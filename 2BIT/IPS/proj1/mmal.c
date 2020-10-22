/********************************************************
 *                     IPS Projekt 1                    *
 *            Vypracoval - Filip Januska (xjanus11)     *
 *                 FIT VUT Brno 2020/2021               *
********************************************************/


/**
 * Implementace My MALloc
 * Demonstracni priklad pro 1. ukol IPS/2020
 * Ales Smrcka
 */

#include "mmal.h"
#include <sys/mman.h> // mmap
#include <stdbool.h> // bool
#include <assert.h> // assert
#include <string.h> // memcpy



#ifdef NDEBUG
/**
 * The structure header encapsulates data of a single memory block.
 *   ---+------+----------------------------+---
 *      |Header|DDD not_free DDDDD...free...|
 *   ---+------+-----------------+----------+---
 *             |-- Header.asize -|
 *             |-- Header.size -------------|
 */
typedef struct header Header;
struct header {

    /**
     * Pointer to the next header. Cyclic list. If there is no other block,
     * points to itself.
     */
    Header *next;

    /// size of the block
    size_t size;

    /**
     * Size of block in bytes allocated for program. asize=0 means the block
     * is not used by a program.
     */
    size_t asize;
};

/**
 * The arena structure.
 *   /--- arena metadata
 *   |     /---- header of the first block
 *   v     v
 *   +-----+------+-----------------------------+
 *   |Arena|Header|.............................|
 *   +-----+------+-----------------------------+
 *
 *   |--------------- Arena.size ---------------|
 */
typedef struct arena Arena;
struct arena {

    /**
     * Pointer to the next arena. Single-linked list.
     */
    Arena *next;

    /// Arena size.
    size_t size;
};

#define PAGE_SIZE (128*1024)

#endif // NDEBUG

Arena *first_arena = NULL;

/**
 * Return size alligned to PAGE_SIZE
 */
static
size_t allign_page(size_t size)
{

    return ((size + (PAGE_SIZE - 1)) / PAGE_SIZE) * PAGE_SIZE;

}

/**
 * Allocate a new arena using mmap.
 * @param req_size requested size in bytes. Should be alligned to PAGE_SIZE.
 * @return pointer to a new arena, if successfull. NULL if error.
 * @pre req_size > sizeof(Arena) + sizeof(Header)
 */

/**
 *   +-----+------------------------------------+
 *   |Arena|....................................|
 *   +-----+------------------------------------+
 *
 *   |--------------- Arena.size ---------------|
 */
static
Arena *arena_alloc(size_t req_size)
{

    if(req_size <= (sizeof(Arena) + sizeof(Header)))
    {
        return NULL;
    }
    // allocate the arena space
    // Allocate enough space for Arena metadata, first Header and 'req_size' usable bytes of memory
    Arena * new_arena = mmap(NULL, req_size + sizeof(Arena) + sizeof(Header), \
                            PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if(new_arena == MAP_FAILED)
    { // mmap error
        return NULL;
    }

    // initialize the arena
    new_arena->next = NULL;
    new_arena->size = req_size;

    return new_arena;


}

/**
 * Appends a new arena to the end of the arena list.
 * @param a     already allocated arena
 */
static
void arena_append(Arena *a)
{
    if(first_arena == NULL)
    {
        first_arena = a;
    }
    else
    {
        // Find the last Arena
        Arena *prev_arena = first_arena;
        while(prev_arena->next != NULL)
        {
            prev_arena = prev_arena->next;
        }
        prev_arena->next = a;

        // Link the new Arena header to the last header of previous Arena
        Header *a_hdr = (Header *) &(a[1]);
        Header *first_hdr = (Header *) &(first_arena[1]);
        Header *prev_hdr = (Header *) &(prev_arena[1]);

        // skip to last header of prev arena
        while(prev_hdr->next != first_hdr)
        {
            prev_hdr = prev_hdr->next;
        }
        prev_hdr->next = a_hdr;

    }
}

/**
 * Header structure constructor (alone, not used block).
 * @param hdr       pointer to block metadata.
 * @param size      size of free block
 * @pre size > 0
 */
/**
 *   +-----+------+------------------------+----+
 *   | ... |Header|........................| ...|
 *   +-----+------+------------------------+----+
 *
 *                |-- Header.size ---------|
 */
static
void hdr_ctor(Header *hdr, size_t size)
{
    if( size <= 0 )
    {
        return;
    }
    hdr->next = hdr;
    hdr->size = size;
    hdr->asize = 0;

}

/**
 * Checks if the given free block should be split in two separate blocks.
 * @param hdr       header of the free block
 * @param size      requested size of data
 * @return true if the block should be split
 * @pre hdr->asize == 0
 * @pre size > 0
 */
static
bool hdr_should_split(Header *hdr, size_t size)
{
    if(hdr->asize != 0 || size <= 0)
    {
        return false;
    }

    // The free space must fit 'size' bytes + space for a second Header
    if(hdr->size >= size + sizeof(Header))
    {
        return true;
    }

    return false;
}

/**
 * Splits one block in two.
 * @param hdr       pointer to header of the big block
 * @param req_size  requested size of data in the (left) block.
 * @return pointer to the new (right) block header.
 * @pre   (hdr->size >= req_size + 2*sizeof(Header))
 */
/**
 * Before:        |---- hdr->size ---------|
 *
 *    -----+------+------------------------+----
 *         |Header|........................|
 *    -----+------+------------------------+----
 *            \----hdr->next---------------^
 */
/**
 * After:         |- req_size -|
 *
 *    -----+------+------------+------+----+----
 *     ... |Header|............|Header|....|
 *    -----+------+------------+------+----+----
 *             \---next--------^  \--next--^
 */
static
Header *hdr_split(Header *hdr, size_t req_size)
{
    if(hdr->size < (req_size + 2* sizeof(Header)))
    {
        return NULL;
    }

    //Move the left header pointer 'req_size' bytes to the right - it will become the address of the right header
    Header *right_hdr = (Header *) (((char *)(hdr)) + req_size );
    hdr_ctor(right_hdr, hdr->size - sizeof(Header) - req_size);

    hdr->size = req_size;
    hdr->asize = req_size;

    right_hdr->next = hdr->next;
    hdr->next = right_hdr;

    return right_hdr;
}

/**
 * Detect if two adjacent blocks could be merged.
 * @param left      left block
 * @param right     right block
 * @return true if two block are free and adjacent in the same arena.
 * @pre left->next == right
 * @pre left != right
 */
static
bool hdr_can_merge(Header *left, Header *right)
{

    if(left->next != right || left == right || right->asize != 0 || left->asize != 0)
    {
        return false;
    }

    // headers are in the same arena only if right header is exactly 'left->size' bytes greater than left header
    if(right == (Header *) (((char *) left) + left->size))
    {
        return true;
    }
    return false;
}

/**
 * Merge two adjacent free blocks.
 * @param left      left block
 * @param right     right block
 * @pre left->next == right
 * @pre left != right
 */
static
void hdr_merge(Header *left, Header *right)
{

    if(left->next != right || left == right)
    {
        return;
    }

    left->next = right->next;
    left->size = left->size + right->size + sizeof(Header);
    left->asize = 0;

}

/**
 * Finds the first free block that fits to the requested size.
 * @param size      requested size
 * @return pointer to the header of the block or NULL if no block is available.
 * @pre size > 0
 */
static
Header *first_fit(size_t size)
{

    if(size <= 0 || first_arena == NULL )
    {
        return NULL;
    }

    // starting from the first header, searches for a block of space
    Header *first_hdr = (Header *) &(first_arena[1]);
    Header *hdr = first_hdr;
    do{
        if(hdr->asize == 0 && hdr->size >= size)
        {
            return hdr;
        }
        hdr = hdr->next;
    }while(hdr != first_hdr && hdr != NULL);

    return NULL;
}

/**
 * Search the header which is the predecessor to the hdr. Note that if
 * @param hdr       successor of the search header
 * @return pointer to predecessor, hdr if there is just one header.
 * @pre first_arena != NULL
 * @post predecessor->next == hdr
 */
static
Header *hdr_get_prev(Header *hdr)
{

    if(first_arena == NULL)
    {
        return NULL;
    }

    if(hdr->next == hdr)
    {
        return hdr;
    }

    Header *pred_hdr = (Header *) &(first_arena[1]);

    while(pred_hdr->next != hdr)
    {
        pred_hdr = pred_hdr->next;
    }

    return pred_hdr;
}

/**
 * Allocate memory. Use first-fit search of available block.
 * @param size      requested size for program
 * @return pointer to allocated data or NULL if error or size = 0.
 */
void *mmalloc(size_t size)
{

    if(size == 0)
    {
        return NULL;
    }
    // arena size must be alligned to PAGE_SIZE and be large enough to fit requested size bytes
    size_t alg_pg_size = allign_page(size + sizeof(Arena) + sizeof(Header));

    // if 'size' is smaller than 2*sizeof(Header) the allocation would be inefficient
    // minimum allocated space will always be at least 2*sizeof(Header) large
    size_t alg_hdr_size = size ;
    if(size < sizeof(Header) * 2)
    {       // modified alignment formula from 'align_page' function
        alg_hdr_size = ( (size + ( (sizeof(Header) * 2) - 1) ) / (sizeof(Header) * 2) ) * (sizeof(Header) * 2);
    }

    Header *hdr = NULL;
    // allocate first arena if needed
    if(first_arena == NULL) {
        first_arena = arena_alloc(alg_pg_size);
        if(first_arena == NULL)
        {
            return NULL;
        }

        hdr = (Header *)&(first_arena[1]);
        hdr_ctor(hdr, first_arena->size);
    }

    // find the first suitable block of space
    hdr = first_fit(alg_hdr_size);

    // all arenas are full - allocate a new one
    if (hdr == NULL)
    {
        Arena * new_arena = arena_alloc(alg_pg_size);
        if(new_arena == NULL)
        {
            return NULL;
        }

        hdr = (Header *)&(new_arena[1]);
        hdr_ctor(hdr, new_arena->size);
        hdr->next = (Header *)&(first_arena[1]);

        arena_append(new_arena);
    }

    // suitable block of space found
    if(hdr_should_split(hdr, alg_hdr_size))
    {
        hdr_split(hdr, alg_hdr_size);
    }
    hdr->asize = size;
    return &(hdr[1]);

}

/**
 * Free memory block.
 * @param ptr       pointer to previously allocated data
 * @pre ptr != NULL
 */
void mfree(void *ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    // header of the block of memory pointed to by 'ptr'
    Header *hdr = &(((Header *)ptr)[-1]);
    hdr->asize = 0;

    // merge with the header to the right, if empty
    if(hdr_can_merge(hdr, hdr->next))
    {
        hdr_merge(hdr, hdr->next);
    }

    // merge with the header to the left, if empty
    Header *pred_hdr = hdr_get_prev(hdr);
    if(hdr_can_merge(pred_hdr, hdr))
    {
        hdr_merge(pred_hdr, hdr);
    }
}

/**
 * Reallocate previously allocated block.
 * @param ptr       pointer to previously allocated data
 * @param size      a new requested size. Size can be greater, equal, or less
 * then size of previously allocated block.
 * @return pointer to reallocated space or NULL if size equals to 0.
 * @post header_of(return pointer)->size == size
 */
void *mrealloc(void *ptr, size_t size)
{
    if(size == 0)
    {
        return NULL;
    }

    // header of the memory block pointed at by 'ptr'
    Header *old_hdr = & (((Header *)ptr)[-1]);

    // memory block is being reduced
    if(size <= old_hdr->asize)
    {
        old_hdr->asize = size;
        return old_hdr;
    }

    // allocate a new memory block
    void *new_ptr = mmalloc(size);
    if(new_ptr == NULL)
    {
        return NULL;
    }

    memcpy(new_ptr, (const void *) ptr, 5);
    mfree(ptr);
    return new_ptr;
}
