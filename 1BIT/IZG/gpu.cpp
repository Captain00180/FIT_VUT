/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/gpu.hpp>



/// \addtogroup gpu_init
/// @{

/**
 * @brief Constructor of GPU
 */
GPU::GPU(){
  /// \todo Zde můžete alokovat/inicializovat potřebné proměnné grafické karty
}

/**
 * @brief Destructor of GPU
 */
GPU::~GPU(){
  /// \todo Zde můžete dealokovat/deinicializovat grafickou kartu

  if(frame_buffer.created)
  {
      deleteFramebuffer();
  }
  for(auto & id : buffer_arr)
  {
      if(isBuffer(id.ID))
        deleteBuffer(id.ID);
  }


}

/// @}

/** \addtogroup buffer_tasks 01. Implementace obslužných funkcí pro buffery
 * @{
 */

/**
 * @brief This function allocates buffer on GPU.
 *
 * @param size size in bytes of new buffer on GPU.
 *
 * @return unique identificator of the buffer
 */
BufferID GPU::createBuffer(uint64_t size) {
    ///  Tato funkce by měla na grafické kartě vytvořit buffer dat.<br>
    /// Velikost bufferu je v parameteru size (v bajtech).<br>
    /// Funkce by měla vrátit unikátní identifikátor identifikátor bufferu.<br>
    /// Na grafické kartě by mělo být možné alkovat libovolné množství bufferů o libovolné velikosti.<br>
    Buffer buff;
    buff.data = malloc(size);
    if (buff.data == NULL) {
        return emptyID;
    }
    buff.size = size;

    //Unused buffer IDs
    if (!freeBufferID_arr.empty())
    {
        BufferID id = freeBufferID_arr.back();
        buffer_arr[id] = buff;
        freeBufferID_arr.pop_back();
        buff.ID = id;
        return id;
    }

    //Assign new unique ID
    buff.ID = buffer_arr.size();
    buffer_arr.push_back(buff);

  return buffer_arr.size() -1;
}

/**
 * @brief This function frees allocated buffer on GPU.
 *
 * @param buffer buffer identificator
 */
void GPU::deleteBuffer(BufferID buffer) {
  /// Tato funkce uvolní buffer na grafické kartě.
  /// Buffer pro smazání je vybrán identifikátorem v parameteru "buffer".
  /// Po uvolnění bufferu je identifikátor volný a může být znovu použit při vytvoření nového bufferu.

  buffer_arr[buffer].size = 0;
  free(buffer_arr[buffer].data);
  buffer_arr[buffer].data = nullptr ;
  buffer_arr[buffer].ID = emptyID;
  freeBufferID_arr.push_back(buffer);
}

/**
 * @brief This function uploads data to selected buffer on the GPU
 *
 * @param buffer buffer identificator
 * @param offset specifies the offset into the buffer's data
 * @param size specifies the size of buffer that will be uploaded
 * @param data specifies a pointer to new data
 */
void GPU::setBufferData(BufferID buffer, uint64_t offset, uint64_t size, void const* data) {
  /// \todo Tato funkce nakopíruje data z cpu na "gpu".<br>
  /// Data by měla být nakopírována do bufferu vybraného parametrem "buffer".<br>
  /// Parametr size určuje, kolik dat (v bajtech) se překopíruje.<br>
  /// Parametr offset určuje místo v bufferu (posun v bajtech) kam se data nakopírují.<br>
  /// Parametr data obsahuje ukazatel na data na cpu pro kopírování.<br>

    if (!isBuffer(buffer))
    {
        return;
    }


    auto *ptr = static_cast<uint8_t *>(buffer_arr[buffer].data);

    memmove( ptr + offset, data, size );

}

/**
 * @brief This function downloads data from GPU.
 *
 * @param buffer specfies buffer
 * @param offset specifies the offset into the buffer from which data will be returned, measured in bytes. 
 * @param size specifies data size that will be copied
 * @param data specifies a pointer to the location where buffer data is returned. 
 */
void GPU::getBufferData(BufferID buffer,
                        uint64_t offset,
                        uint64_t size,
                        void*    data)
{
  /// \todo Tato funkce vykopíruje data z "gpu" na cpu.
  /// Data by měla být vykopírována z bufferu vybraného parametrem "buffer".<br>
  /// Parametr size určuje kolik dat (v bajtech) se překopíruje.<br>
  /// Parametr offset určuje místo v bufferu (posun v bajtech) odkud se začne kopírovat.<br>
  /// Parametr data obsahuje ukazatel, kam se data nakopírují.<br>

  if (!isBuffer(buffer))
  {
      return;
  }

  auto *ptr = static_cast<uint8_t *>(buffer_arr[buffer].data);

  memmove(data, ptr + offset, size);

}

/**
 * @brief This function tests if buffer exists
 *
 * @param buffer selected buffer id
 *
 * @return true if buffer points to existing buffer on the GPU.
 */
bool GPU::isBuffer(BufferID buffer) { 
  /// \todo Tato funkce by měla vrátit true pokud buffer je identifikátor existující bufferu.<br>
  /// Tato funkce by měla vrátit false, pokud buffer není identifikátor existujícího bufferu. (nebo bufferu, který byl smazán).<br>
  /// Pro emptyId vrací false.<br>

  // Invalid BufferID
  if (buffer == emptyID || buffer >= buffer_arr.size())
  {
      return false;
  }

    return buffer_arr[buffer].ID != emptyID;

}

/// @}

/**
 * \addtogroup vertexpuller_tasks 02. Implementace obslužných funkcí pro vertex puller
 * @{
 */

/**
 * @brief This function creates new vertex puller settings on the GPU,
 *
 * @return unique vertex puller identificator
 */
ObjectID GPU::createVertexPuller     (){
  /// \todo Tato funkce vytvoří novou práznou tabulku s nastavením pro vertex puller.<br>
  /// Funkce by měla vrátit identifikátor nové tabulky.
  /// Prázdná tabulka s nastavením neobsahuje indexování a všechny čtecí hlavy jsou vypnuté.

    VertexPuller vert_pull;
    vert_pull.indexing.indexing_id = emptyID;
    vert_pull.ID = emptyID;
    for (auto & pullerhead : vert_pull.pullerheads)
    {
        pullerhead.id = emptyID;
        pullerhead.enabled = false;
        pullerhead.offset = 0;
        pullerhead.stride = 0;
        pullerhead.type = AttributeType::EMPTY;
    }

    // Reuse old VP ID
    if (!freeVertID_arr.empty())
    {
        VertexPullerID id = freeVertID_arr.back();
        vert_pull_arr[id] = vert_pull;
        freeVertID_arr.pop_back();
        vert_pull.ID = id;
        return id;
    }
    // Set new unique ID
    vert_pull.ID = vert_pull_arr.size();
    vert_pull_arr.push_back(vert_pull);

    return vert_pull_arr.size() - 1;
}

/**
 * @brief This function deletes vertex puller settings
 *
 * @param vao vertex puller identificator
 */
void     GPU::deleteVertexPuller     (VertexPullerID vao){
  /// \todo Tato funkce by měla odstranit tabulku s nastavení pro vertex puller.<br>
  /// Parameter "vao" obsahuje identifikátor tabulky s nastavením.<br>
  /// Po uvolnění nastavení je identifiktátor volný a může být znovu použit.<br>

    freeVertID_arr.push_back(vao);

    vert_pull_arr[vao].ID = emptyID;

}

/**
 * @brief This function sets one vertex puller reading head.
 *
 * @param vao identificator of vertex puller
 * @param head id of vertex puller head
 * @param type type of attribute
 * @param stride stride in bytes
 * @param offset offset in bytes
 * @param buffer id of buffer
 */
void     GPU::setVertexPullerHead    (VertexPullerID vao,uint32_t head,AttributeType type,uint64_t stride,uint64_t offset,BufferID buffer){
  /// \todo Tato funkce nastaví jednu čtecí hlavu vertex pulleru.<br>
  /// Parametr "vao" vybírá tabulku s nastavením.<br>
  /// Parametr "head" vybírá čtecí hlavu vybraného vertex pulleru.<br>
  /// Parametr "type" nastaví typ atributu, který čtecí hlava čte. Tímto se vybere kolik dat v bajtech se přečte.<br>
  /// Parametr "stride" nastaví krok čtecí hlavy.<br>
  /// Parametr "offset" nastaví počáteční pozici čtecí hlavy.<br>
  /// Parametr "buffer" vybere buffer, ze kterého bude čtecí hlava číst.<br>

  VertexPuller vert_pull = vert_pull_arr[vao];

  vert_pull.pullerheads[head].type = type;
  vert_pull.pullerheads[head].stride = stride;
  vert_pull.pullerheads[head].offset = offset;
  vert_pull.pullerheads[head].id = buffer;

  vert_pull_arr[vao] = vert_pull;

}

/**
 * @brief This function sets vertex puller indexing.
 *
 * @param vao vertex puller id
 * @param type type of index
 * @param buffer buffer with indices
 */
void     GPU::setVertexPullerIndexing(VertexPullerID vao,IndexType type,BufferID buffer){
  /// \todo Tato funkce nastaví indexování vertex pulleru.
  /// Parametr "vao" vybírá tabulku s nastavením.<br>
  /// Parametr "type" volí typ indexu, který je uložený v bufferu.<br>
  /// Parametr "buffer" volí buffer, ve kterém jsou uloženy indexy.<br>

  vert_pull_arr[vao].indexing.type = type;
  vert_pull_arr[vao].indexing.indexing_id = buffer;

}

/**
 * @brief This function enables vertex puller's head.
 *
 * @param vao vertex puller 
 * @param head head id
 */
void     GPU::enableVertexPullerHead (VertexPullerID vao,uint32_t head){
  /// \todo Tato funkce povolí čtecí hlavu daného vertex pulleru.<br>
  /// Pokud je čtecí hlava povolena, hodnoty z bufferu se budou kopírovat do atributu vrcholů vertex shaderu.<br>
  /// Parametr "vao" volí tabulku s nastavením vertex pulleru (vybírá vertex puller).<br>
  /// Parametr "head" volí čtecí hlavu.<br>

  vert_pull_arr[vao].pullerheads[head].enabled = true;

}

/**
 * @brief This function disables vertex puller's head
 *
 * @param vao vertex puller id
 * @param head head id
 */
void     GPU::disableVertexPullerHead(VertexPullerID vao,uint32_t head){
  /// \todo Tato funkce zakáže čtecí hlavu daného vertex pulleru.<br>
  /// Pokud je čtecí hlava zakázána, hodnoty z bufferu se nebudou kopírovat do atributu vrcholu.<br>
  /// Parametry "vao" a "head" vybírají vertex puller a čtecí hlavu.<br>

  vert_pull_arr[vao].pullerheads[head].enabled = false;

}

/**
 * @brief This function selects active vertex puller.
 *
 * @param vao id of vertex puller
 */
void     GPU::bindVertexPuller       (VertexPullerID vao){
  /// \todo Tato funkce aktivuje nastavení vertex pulleru.<br>
  /// Pokud je daný vertex puller aktivován, atributy z bufferů jsou vybírány na základě jeho nastavení.<br>

    if (isVertexPuller(vao))
    {
        active_vert_pull = vao;
    }

}

/**
 * @brief This function deactivates vertex puller.
 */
void     GPU::unbindVertexPuller     (){
  /// \todo Tato funkce deaktivuje vertex puller.
  /// To většinou znamená, že se vybere neexistující "emptyID" vertex puller.

  active_vert_pull = emptyID;

}

/**
 * @brief This function tests if vertex puller exists.
 *
 * @param vao vertex puller
 *
 * @return true, if vertex puller "vao" exists
 */
bool     GPU::isVertexPuller         (VertexPullerID vao){
  /// \todo Tato funkce otestuje, zda daný vertex puller existuje.
  /// Pokud ano, funkce vrací true.

  // Invalid ID or ID among free VP IDs waiting to be reused
  if (vao == emptyID || vao >= vert_pull_arr.size() || std::find(freeVertID_arr.begin(), freeVertID_arr.end(), vao) != freeVertID_arr.end())
  {
      return false;
  }

  return true;

}

/// @}

/** \addtogroup program_tasks 03. Implementace obslužných funkcí pro shader programy
 * @{
 */

/**
 * @brief This function creates new shader program.
 *
 * @return shader program id
 */
ProgramID        GPU::createProgram         (){
  /// \todo Tato funkce by měla vytvořit nový shader program.<br>
  /// Funkce vrací unikátní identifikátor nového proramu.<br>
  /// Program je seznam nastavení, které obsahuje: ukazatel na vertex a fragment shader.<br>
  /// Dále obsahuje uniformní proměnné a typ výstupních vertex attributů z vertex shaderu, které jsou použity pro interpolaci do fragment atributů.<br>

  ShaderProgram new_prog;
  new_prog.vert_shader = nullptr;
  new_prog.frag_shader = nullptr;

  for (auto & attrib : new_prog.attribs)
  {
      attrib = AttributeType::EMPTY;
  }

  if (!freeProgID_arr.empty())
  {
      ProgramID id = freeProgID_arr.back();
      new_prog.ID = id;
      shader_prog_arr[id] = new_prog;
      freeProgID_arr.pop_back();
      return id;
  }

  new_prog.ID = shader_prog_arr.size();
  shader_prog_arr.push_back(new_prog);

  return shader_prog_arr.size() - 1;
}

/**
 * @brief This function deletes shader program
 *
 * @param prg shader program id
 */
void             GPU::deleteProgram         (ProgramID prg){
  /// \todo Tato funkce by měla smazat vybraný shader program.<br>
  /// Funkce smaže nastavení shader programu.<br>
  /// Identifikátor programu se stane volným a může být znovu využit.<br>

  freeProgID_arr.push_back(prg);
  shader_prog_arr[prg].ID = emptyID;


}

/**
 * @brief This function attaches vertex and frament shader to shader program.
 *
 * @param prg shader program
 * @param vs vertex shader 
 * @param fs fragment shader
 */
void             GPU::attachShaders         (ProgramID prg,VertexShader vs,FragmentShader fs){
  /// \todo Tato funkce by měla připojít k vybranému shader programu vertex a fragment shader.

  shader_prog_arr[prg].frag_shader = fs;
  shader_prog_arr[prg].vert_shader = vs;

}

/**
 * @brief This function selects which vertex attributes should be interpolated during rasterization into fragment attributes.
 *
 * @param prg shader program
 * @param attrib id of attribute
 * @param type type of attribute
 */
void             GPU::setVS2FSType          (ProgramID prg,uint32_t attrib,AttributeType type){
  /// \todo tato funkce by měla zvolit typ vertex atributu, který je posílán z vertex shaderu do fragment shaderu.<br>
  /// V průběhu rasterizace vznikají fragment.<br>
  /// Fragment obsahují fragment atributy.<br>
  /// Tyto atributy obsahují interpolované hodnoty vertex atributů.<br>
  /// Tato funkce vybere jakého typu jsou tyto interpolované atributy.<br>
  /// Bez jakéhokoliv nastavení jsou atributy prázdne AttributeType::EMPTY<br>

    shader_prog_arr[prg].attribs[attrib] = type;

}

/**
 * @brief This function actives selected shader program
 *
 * @param prg shader program id
 */
void             GPU::useProgram            (ProgramID prg){
  /// \todo tato funkce by měla vybrat aktivní shader program.

  active_shad_prog = prg;

}

/**
 * @brief This function tests if selected shader program exists.
 *
 * @param prg shader program
 *
 * @return true, if shader program "prg" exists.
 */
bool             GPU::isProgram             (ProgramID prg){
  /// \todo tato funkce by měla zjistit, zda daný program existuje.<br>
  /// Funkce vráti true, pokud program existuje.<br>

  if(prg == emptyID || prg >= shader_prog_arr.size() || std::find( freeProgID_arr.begin(), freeProgID_arr.end(), prg) != freeProgID_arr.end() )
  {
      return false;
  }

  return true;

}

/**
 * @brief This function sets uniform value (1 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void             GPU::programUniform1f      (ProgramID prg,uint32_t uniformId,float     const&d){
  /// \todo tato funkce by měla nastavit uniformní proměnnou shader programu.<br>
  /// Parametr "prg" vybírá shader program.<br>
  /// Parametr "uniformId" vybírá uniformní proměnnou. Maximální počet uniformních proměnných je uložen v programné \link maxUniforms \endlink.<br>
  /// Parametr "d" obsahuje data (1 float).<br>

  shader_prog_arr[prg].uniforms.uniform[uniformId].v1 = d;


}

/**
 * @brief This function sets uniform value (2 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void             GPU::programUniform2f      (ProgramID prg,uint32_t uniformId,glm::vec2 const&d){
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 2 floaty.

   shader_prog_arr[prg].uniforms.uniform[uniformId].v2 = d;



}

/**
 * @brief This function sets uniform value (3 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void             GPU::programUniform3f      (ProgramID prg,uint32_t uniformId,glm::vec3 const&d){
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 3 floaty.


    shader_prog_arr[prg].uniforms.uniform[uniformId].v3 = d;

}

/**
 * @brief This function sets uniform value (4 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void             GPU::programUniform4f      (ProgramID prg,uint32_t uniformId,glm::vec4 const&d){
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 4 floaty.

    shader_prog_arr[prg].uniforms.uniform[uniformId].v4 = d;

}

/**
 * @brief This function sets uniform value (4 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void             GPU::programUniformMatrix4f(ProgramID prg,uint32_t uniformId,glm::mat4 const&d){
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává matici 4x4 (16 floatů).


    shader_prog_arr[prg].uniforms.uniform[uniformId].m4 = d;

}

/// @}





/** \addtogroup framebuffer_tasks 04. Implementace obslužných funkcí pro framebuffer
 * @{
 */

/**
 * @brief This function creates framebuffer on GPU.
 *
 * @param width width of framebuffer
 * @param height height of framebuffer
 */
void GPU::createFramebuffer      (uint32_t width,uint32_t height){
  /// \todo Tato funkce by měla alokovat framebuffer od daném rozlišení.<br>
  /// Framebuffer se skládá z barevného a hloukového bufferu.<br>
  /// Buffery obsahují width x height pixelů.<br>
  /// Barevný pixel je složen z 4 x uint8_t hodnot - to reprezentuje RGBA barvu.<br>
  /// Hloubkový pixel obsahuje 1 x float - to reprezentuje hloubku.<br>
  /// Nultý pixel framebufferu je vlevo dole.<br>

  uint64_t pixel_count = width * height;

  frame_buffer.created = true;
  frame_buffer.height = height;
  frame_buffer.width = width;

  frame_buffer.depth_buffer = new float[pixel_count];
  frame_buffer.color_buffer = new uint8_t[pixel_count * 4];



}

/**
 * @brief This function deletes framebuffer.
 */
void GPU::deleteFramebuffer      (){
  /// \todo tato funkce by měla dealokovat framebuffer.

  frame_buffer.height = 0;
  frame_buffer.width = 0;
  frame_buffer.created = false;
  delete[] frame_buffer.color_buffer;
  delete[] frame_buffer.depth_buffer;


}

/**
 * @brief This function resizes framebuffer.
 *
 * @param width new width of framebuffer
 * @param height new heght of framebuffer
 */
void     GPU::resizeFramebuffer(uint32_t width,uint32_t height){
  /// \todo Tato funkce by měla změnit velikost framebuffer.

  GPU::deleteFramebuffer();
  GPU::createFramebuffer(width, height);
}

/**
 * @brief This function returns pointer to color buffer.
 *
 * @return pointer to color buffer
 */
uint8_t* GPU::getFramebufferColor  (){
  /// \todo Tato funkce by měla vrátit ukazatel na začátek barevného bufferu.<br>

  return frame_buffer.color_buffer;
}

/**
 * @brief This function returns pointer to depth buffer.
 *
 * @return pointer to dept buffer.
 */
float* GPU::getFramebufferDepth    (){
  /// \todo tato funkce by mla vrátit ukazatel na začátek hloubkového bufferu.<br>
  return frame_buffer.depth_buffer;
}

/**
 * @brief This function returns width of framebuffer
 *
 * @return width of framebuffer
 */
uint32_t GPU::getFramebufferWidth (){
  /// \todo Tato funkce by měla vrátit šířku framebufferu.
  return frame_buffer.width;
}

/**
 * @brief This function returns height of framebuffer.
 *
 * @return height of framebuffer
 */
uint32_t GPU::getFramebufferHeight(){
  /// \todo Tato funkce by měla vrátit výšku framebufferu.
  return frame_buffer.height;
}

/// @}

/** \addtogroup draw_tasks 05. Implementace vykreslovacích funkcí
 * Bližší informace jsou uvedeny na hlavní stránce dokumentace.
 * @{
 */

/**
 * @brief This functino clears framebuffer.
 *
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel
 */
void            GPU::clear                 (float r,float g,float b,float a){
  /// \todo Tato funkce by měla vyčistit framebuffer.<br>
  /// Barevný buffer vyčistí na barvu podle parametrů r g b a (0 - nulová intenzita, 1 a větší - maximální intenzita).<br>
  /// (0,0,0) - černá barva, (1,1,1) - bílá barva.<br>
  /// Hloubkový buffer nastaví na takovou hodnotu, která umožní rasterizaci trojúhelníka, který leží v rámci pohledového tělesa.<br>
  /// Hloubka by měla být tedy větší než maximální hloubka v NDC (normalized device coordinates).<br>


  size_t pix_count = frame_buffer.width * frame_buffer.height;

  r = cut_to_max(r, 1);
  g = cut_to_max(g, 1);
  b = cut_to_max(b, 1);
  a = cut_to_max(a, 1);

  auto r_int = static_cast<uint8_t> ( r * 255);
  auto g_int = static_cast<uint8_t> ( g * 255);
  auto b_int = static_cast<uint8_t> ( b * 255);
  auto a_int = static_cast<uint8_t> ( a * 255);


    for(size_t i = 0; i < (pix_count * 4); i+=4)
  {
      frame_buffer.color_buffer[i] = r_int;
      frame_buffer.color_buffer[i+1] = g_int;
      frame_buffer.color_buffer[i+2] = b_int;
      frame_buffer.color_buffer[i+3] = a_int;
  }

  for(size_t i = 0; i < pix_count; ++i)
  {
        frame_buffer.depth_buffer[i] = +1.42f;
  }

}


// Interpolate the z coordinate
template <typename att_type, typename flt = float>
att_type     GPU::interpolate           (flt lambda_A, flt lambda_B, flt lambda_C, flt A_w, flt B_w, flt C_w, att_type A, att_type B, att_type C){
    return ( ( ( (A * lambda_A ) / A_w) + ( ( B * lambda_B ) / B_w ) + ( ( C * lambda_C ) / C_w ) ) /  ( (lambda_A / A_w) + (lambda_B / B_w) + (lambda_C / C_w) ) );
}



// Calculate the edge function value for a point and a line defined by two vertices
float           GPU::edge_function         (OutVertex vert_A, OutVertex vert_B, double p_x, double p_y){
    return ( (vert_A.gl_Position[0] - vert_B.gl_Position[0]) * (p_y - vert_A.gl_Position[1]) - (vert_A.gl_Position[1] - vert_B.gl_Position[1]) * (p_x - vert_A.gl_Position[0]));
}



float     GPU::max_of_3              (float a, float b, float c){
    if (a >= b && a >= c)
    {
        return a;
    }
    if (b >= a && b >= c)
    {
        return b;
    }
    return c;

}

float     GPU::min_of_3              (float a, float b, float c){
    if (a <= b && a <= c)
    {
        return a;
    }
    if (b <= a && b <= c)
    {
        return b;
    }
    return c;
}

float       GPU::cut_to_max            (float x, float y)
{
    if(x > y)
    {
        return y;
    }
    return x;
}

float       GPU::cut_to_min            (float x, float y)
{
    if(x < y)
    {
        return y;
    }
    return x;

}



void            GPU::drawTriangles         (uint32_t  nofVertices){
  /// \todo Tato funkce vykreslí trojúhelníky podle daného nastavení.<br>
  /// Vrcholy se budou vybírat podle nastavení z aktivního vertex pulleru (pomocí bindVertexPuller).<br>
  /// Vertex shader a fragment shader se zvolí podle aktivního shader programu (pomocí useProgram).<br>
  /// Parametr "nofVertices" obsahuje počet vrcholů, který by se měl vykreslit (3 pro jeden trojúhelník).<br>




  // Vector holding Out Vertices - they are stored here after being processed by the Vertex Processor
  std::vector<OutVertex> out_vertices;
  ShaderProgram shad_prog = shader_prog_arr[active_shad_prog];

  for (uint64_t i = 0; i < nofVertices ; ++i)
    {
/**************************************************************************
*                        VERTEX PULLER                                   *
*                        buffer -> InVertex                              *
**************************************************************************/

      InVertex in_vertex;
      in_vertex.gl_VertexID = 0;
      VertexPuller vert_pull = vert_pull_arr[active_vert_pull];

      //set Vertex ID from Indexing buffer
      if (vert_pull.indexing.indexing_id != emptyID)
      {
          auto size = static_cast<__uint64_t >( vert_pull.indexing.type);
          getBufferData(vert_pull.indexing.indexing_id, i * size, size, &in_vertex.gl_VertexID);


      }
      //set Vertex ID based on the number of Vertex Shader calls
      else
      {
          in_vertex.gl_VertexID = i;
      }


      // Read Vertex atributes
      for ( int idx = 0; idx < maxAttributes; ++idx)
      {
          // Enabled Vertex Puller Head == read data from its buffer
          if (vert_pull.pullerheads[idx].enabled) {
              BufferID buffer = vert_pull.pullerheads[idx].id;
              uint64_t stride = vert_pull.pullerheads[idx].stride;
              uint64_t offset = vert_pull.pullerheads[idx].offset;
              offset += stride * in_vertex.gl_VertexID;

              // Read data into suitable Vertex Attribute corresponding to the Attribute Type stored in puller head
              switch (vert_pull.pullerheads[idx].type) {
                  case AttributeType::FLOAT: {
                      uint64_t size = sizeof(in_vertex.attributes[idx].v1);
                      getBufferData(buffer, offset, size, &in_vertex.attributes[idx].v1);
                      break;
                  }
                  case AttributeType::VEC2: {
                      uint64_t size = sizeof(in_vertex.attributes[idx].v2);
                      getBufferData(buffer, offset, size, &in_vertex.attributes[idx].v2);
                      break;
                  }
                  case AttributeType::VEC3:
                  {
                      uint64_t size = sizeof(in_vertex.attributes[idx].v3);
                      getBufferData(buffer, offset, size, &in_vertex.attributes[idx].v3);
                      break;
                  }
                  case AttributeType::VEC4:
                  {
                      uint64_t size = sizeof(in_vertex.attributes[idx].v4);
                      getBufferData(buffer, offset, size, &in_vertex.attributes[idx].v4);
                      break;
                  }

              }
          }
      }

      /********************************************************************************
       *                        VERTEX PROCESSOR                                      *
       *                        InVertex -> OutVertex                                 *
      *********************************************************************************/
      OutVertex out_vertex;


      shad_prog.vert_shader(out_vertex, in_vertex, shad_prog.uniforms);


      out_vertices.push_back(out_vertex);
  }


    /**********************************************************************************
     *                          PRIMITIVE ASSEMBLY                                    *
     *                          3xOutvertex -> Triangle                               *
     **********************************************************************************/
    // Construct a triangle out of 3 vertices
    std::vector <Triangle> triangles;


    for (size_t i = 0; i < out_vertices.size() ; i+=3)
    {
        Triangle new_trig;
        new_trig.vertices[0] = out_vertices[i];
        new_trig.vertices[1] = out_vertices[i + 1];
        new_trig.vertices[2] = out_vertices[i + 2];

        triangles.push_back(new_trig);
    }



    /***********************************************************************************
     *                              CLIPPING                                           *
     *                            Triangle-> {0-2} triangles                           *
     ***********************************************************************************/
     //  Vector holding triangles produced after clipping
     std::vector <Triangle> clipped_triangles;
    // Clip each triangle by the near plane equation
    for (auto & triangle: triangles)
    {
        // Vertices before near plane - good boys
        std::vector<OutVertex> good_vertices;
        // Vertices behind near plane - bad dogs
        std::vector<OutVertex> bad_vertices;

        // Compare each vertex's Z and W coordinate
        for (auto & vertex: triangle.vertices)
        {
            //          -Aw   <=  Az
            if ((vertex.gl_Position[3] * -1) <= vertex.gl_Position[2])
            {
                good_vertices.push_back(vertex);
            } else
            {
                bad_vertices.push_back(vertex);
            }

        }


        // Triangle is behind near plane - disregard the dude
        if(good_vertices.empty())
        {
            continue;
        }
        // Triangle is before the near plane - nothing to do
        if (bad_vertices.empty())
        {
            clipped_triangles.push_back(triangle);
            continue;
        }

        // Two new vertices will be created and used to create 1 or 2 new triangles
        OutVertex new_vertices[2];

        int counter = 0;

        // For each combination of good vertices and bad vertices - Traverse the line between them, find the vertex for the new triangles
        for (auto &gvert : good_vertices)
        {
            // This cycle represents a single line connecting a point before and a point behind the near plane
            for (auto &bvert : bad_vertices)
            {
                // Calculate 't' parameter for the intersection point
                //        ( -       Aw               -       Az            ) / (        Bw            -         Aw           +          Bz          -       Az            )
                float t = (-1 * gvert.gl_Position[3] - gvert.gl_Position[2]) / ( bvert.gl_Position[3] - gvert.gl_Position[3] + bvert.gl_Position[2] - gvert.gl_Position[2]);


                // Calculate new vertex's position
                for (size_t i = 0; i < 4; ++i)
                {
                    new_vertices[counter].gl_Position[i] = gvert.gl_Position[i] + t * ( bvert.gl_Position[i] - gvert.gl_Position[i] );
                }

                // Calculate new vertex's attributes, if they're set by setVS2FSType
                for(int i = 0; i < maxAttributes; ++i) {
                    if (shad_prog.attribs[i] != AttributeType::EMPTY) {
                        int idx = i;

                        switch (shad_prog.attribs[idx]) {
                            case AttributeType::FLOAT: {
                                float gvert_att = gvert.attributes[idx].v1;
                                float bvert_att = bvert.attributes[idx].v1;

                                new_vertices[counter].attributes[idx].v1 = (gvert_att + t * (bvert_att - gvert_att));

                                break;
                            }
                            case AttributeType::VEC2: {
                                glm::vec2 gvert_att = gvert.attributes[idx].v2;
                                glm::vec2 bvert_att = bvert.attributes[idx].v2;

                                for (int vect_idx = 0; vect_idx < 2; ++vect_idx) {
                                    new_vertices[counter].attributes[idx].v2[vect_idx] = (gvert_att[vect_idx] + t *
                                                                                                                (bvert_att[vect_idx] -
                                                                                                                 gvert_att[vect_idx]));
                                }

                                break;
                            }
                            case AttributeType::VEC3: {
                                glm::vec3 gvert_att = gvert.attributes[idx].v3;
                                glm::vec3 bvert_att = bvert.attributes[idx].v3;

                                for (int vect_idx = 0; vect_idx < 3; ++vect_idx) {
                                    new_vertices[counter].attributes[idx].v3[vect_idx] = (gvert_att[vect_idx] + t *
                                                                                                                (bvert_att[vect_idx] -
                                                                                                                 gvert_att[vect_idx]));
                                }

                                break;
                            }
                            case AttributeType::VEC4: {
                                glm::vec4 gvert_att = gvert.attributes[idx].v4;
                                glm::vec4 bvert_att = bvert.attributes[idx].v4;

                                for (int vect_idx = 0; vect_idx < 4; ++vect_idx) {
                                    new_vertices[counter].attributes[idx].v4[vect_idx] = (gvert_att[vect_idx] + t *
                                                                                                                (bvert_att[vect_idx] -
                                                                                                                 gvert_att[vect_idx]));
                                }

                                break;
                            }
                        }   //switch end


                    }   // vertex attributes calculations end
                }

                //
                // New vertex is created
                //

                ++counter;

            }   // bad_vertex loop end

        }   // good_vertex loop end

        //
        // Two new vertices are created - time to create new triangles
        //


        // One triangle will be created
        if (good_vertices.size() == 1)
        {
            Triangle new_trig;
            new_trig.vertices[0] = good_vertices[0];
            new_trig.vertices[1] = new_vertices[0];
            new_trig.vertices[2] = new_vertices[1];

            clipped_triangles.push_back(new_trig);
         }
        // Two triangles will be created
        else{
            Triangle new_trig_1;
            new_trig_1.vertices[0] = good_vertices[0];
            new_trig_1.vertices[1] = good_vertices[1];
            new_trig_1.vertices[2] = new_vertices[1];

            Triangle new_trig_2;
            new_trig_2.vertices[1] = good_vertices[0];
            new_trig_2.vertices[0] = new_vertices[0];
            new_trig_2.vertices[2] = new_vertices[1];

            clipped_triangles.push_back(new_trig_1);
            clipped_triangles.push_back(new_trig_2);
        }


    }   // Triangle clipping end

    /************************************************************************
     *                      PERSPECTIVE DIVISION                            *
     *              triangle[x, y, z] -> triangle[x/w, y/w, z/w]            *
    *************************************************************************/

    for (auto & triangle : clipped_triangles)
    {
        for(auto & vertex : triangle.vertices)
        {
            for(int i = 0; i < 3; ++i)
            {
                vertex.gl_Position[i] /= vertex.gl_Position[3];
            }
        }
    }

    /************************************************************************
     *                      VIEWPORT TRANSFORMATION                         *
     *                    ([x,y] + 1) / 2 * width/height                    *
    ************************************************************************/
    for (auto & triangle : clipped_triangles)
    {
        for (auto & vertex : triangle.vertices)
        {
            vertex.gl_Position[0] = ( (vertex.gl_Position[0] + 1) / 2 ) * (frame_buffer.width );
            vertex.gl_Position[1] = ( (vertex.gl_Position[1] + 1) / 2 ) * (frame_buffer.height);
        }
    }

    /*************************************************************************
     *                          RASTERIZATION                                *
    *************************************************************************/

    // Pined's algorithm
    for (auto & triangle : clipped_triangles)
    {

        OutVertex A = triangle.vertices[0];
        auto A_x = A.gl_Position[0];
        auto A_y = A.gl_Position[1];
        auto A_z = A.gl_Position[2];
        auto A_w = A.gl_Position[3];

        OutVertex B = triangle.vertices[1];
        auto B_x = B.gl_Position[0];
        auto B_y = B.gl_Position[1];
        auto B_z = B.gl_Position[2];
        auto B_w = B.gl_Position[3];

        OutVertex C = triangle.vertices[2];
        auto C_x = C.gl_Position[0];
        auto C_y = C.gl_Position[1];
        auto C_z = C.gl_Position[2];
        auto C_w = C.gl_Position[3];


        // Find surrounding rectangle
        auto max_x = static_cast<int>( ceilf(max_of_3(A_x,B_x, C_x )));
        auto max_y = static_cast<int>( ceilf(max_of_3(A_y,B_y, C_y )));

        auto min_x = static_cast<int>( floorf(min_of_3(A_x,B_x, C_x)));
        auto min_y = static_cast<int>( floorf(min_of_3(A_y,B_y, C_y)));


        // Cut max and min - if(max > framebuffer limit) -> max = limit
        //                 - if(min < 0) -> min = 0
        max_x = cut_to_max(max_x, frame_buffer.width);
        max_y = cut_to_max(max_y, frame_buffer.height);

        min_x = cut_to_min(min_x, 0);
        min_y = cut_to_min(min_y, 0);

        // Calculate the initial edge function values for x_min and y_min

        float edge_value_1 = edge_function(A, B,static_cast<float>(min_x + 0.5f),static_cast<float>(min_y  + 0.5f));
        float edge_value_2 = edge_function(B, C,static_cast<float>(min_x + 0.5f),static_cast<float>(min_y + 0.5f));
        float edge_value_3 = edge_function(C, A,static_cast<float>(min_x + 0.5f),static_cast<float>(min_y + 0.5f));


        float edge_value_1_delta_x = A_x - B_x;
        float edge_value_2_delta_x = B_x - C_x;
        float edge_value_3_delta_x = C_x - A_x;

        float edge_value_1_delta_y = A_y - B_y;
        float edge_value_2_delta_y = B_y - C_y;
        float edge_value_3_delta_y = C_y - A_y;

        // Iterate through each pixel within this rectangle
        for(auto y_coord = min_y; y_coord < max_y; ++y_coord)
        {
            size_t counter = 0;
            for (auto x_coord = min_x; x_coord < max_x; ++x_coord)
            {
                if( (edge_value_1 <= 0 && edge_value_2 <= 0 && edge_value_3 <= 0)   )
                {
                    // Point lies within the triangle - create a Fragment
                        InFragment new_fragment;
                        float x_coord_mid = x_coord + 0.5f;
                        float y_coord_mid = y_coord + 0.5f;
                        new_fragment.gl_FragCoord[0] = x_coord_mid;
                        new_fragment.gl_FragCoord[1] = y_coord_mid;


                        // Calculate barymetric coordinates for interpolation
                        // P = Found point
                        // A = vertex[0]
                        // B = vertex[1]
                        // C = vertex[2]

                        // Conversion of Cartesian coordinates to barycentric coordinates (lambdas) according to the equations from
                        // https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates


                        float lambda_A =  ((B_y - C_y) * (x_coord_mid - C_x) + (C_x - B_x) * (y_coord_mid - C_y))
                                                                          ;//  /
                                            // ( (B_y - C_y) * (A_x - C_x) + (C_x - B_x) * (A_y - C_y));
                        float lambda_B = ( (C_y - A_y) * (x_coord_mid - C_x) + (A_x - C_x) * (y_coord_mid - C_y))
                                                        ;//
                                          //( (B_y - C_y) * (A_x - C_x) + (C_x - B_x) * (A_y - C_y) );
                        float lambda_C =   (( (B_y - C_y) * (A_x - C_x) + (C_x - B_x) * (A_y - C_y) )) - lambda_A - lambda_B;



                        // Interpolation of z coordinate
                        new_fragment.gl_FragCoord[2] = interpolate (lambda_A, lambda_B, lambda_C, A_w, B_w, C_w, A_z, B_z, C_z);

                        // Interpolation of attributes
                        for(int at_id = 0; at_id < maxAttributes; ++at_id) {
                            if (shad_prog.attribs[at_id] != AttributeType::EMPTY) {
                                switch (shad_prog.attribs[at_id]) {
                                    case AttributeType::FLOAT: {
                                        new_fragment.attributes[at_id].v1 = interpolate(lambda_A, lambda_B, lambda_C,
                                                                                        A_w, B_w, C_w,
                                                                                        A.attributes[at_id].v1,
                                                                                        B.attributes[at_id].v1,
                                                                                        C.attributes[at_id].v1);
                                        break;
                                    }
                                    case AttributeType::VEC2: {
                                        new_fragment.attributes[at_id].v2 = interpolate(lambda_A, lambda_B, lambda_C,
                                                                                        A_w, B_w, C_w,
                                                                                        A.attributes[at_id].v2,
                                                                                        B.attributes[at_id].v2,
                                                                                        C.attributes[at_id].v2);
                                        break;
                                    }
                                    case AttributeType::VEC3: {
                                        new_fragment.attributes[at_id].v3 = interpolate(lambda_A, lambda_B, lambda_C,
                                                                                        A_w, B_w, C_w,
                                                                                        A.attributes[at_id].v3,
                                                                                        B.attributes[at_id].v3,
                                                                                        C.attributes[at_id].v3);
                                        break;
                                    }
                                    case AttributeType::VEC4: {
                                        new_fragment.attributes[at_id].v4 = interpolate(lambda_A, lambda_B, lambda_C,
                                                                                        A_w, B_w, C_w,
                                                                                        A.attributes[at_id].v4,
                                                                                        B.attributes[at_id].v4,
                                                                                        C.attributes[at_id].v4);
                                        break;
                                    }
                                }
                            }
                        }


                        //     index =          x + y * width

                        size_t fb_indx = ( y_coord  * frame_buffer.width *4) + (x_coord *4);

                        /**********************************************************
                        *                  FRAGMENT PROCESSOR                    *
                        *                  InFragment -> OutFragment             *
                       ***********************************************************/
                        OutFragment processed_fragment;
                        shad_prog.frag_shader(processed_fragment, new_fragment, shad_prog.uniforms);

                        // Test new fragment's depth

                       /**********************************************************
                       *              PER-FRAGMENT OPERATIONS                   *
                       *             OutFragment -> framebuffer                 *
                      ***********************************************************/

                        if (frame_buffer.depth_buffer[fb_indx/4] > new_fragment.gl_FragCoord[2])
                        {


                            for (int i = 0; i < 4; ++i)
                            {
                                processed_fragment.gl_FragColor[i] = std::min(1.f, processed_fragment.gl_FragColor[i]);
                            }

                            frame_buffer.depth_buffer[fb_indx/4] = new_fragment.gl_FragCoord[2];
                            frame_buffer.color_buffer[fb_indx] = processed_fragment.gl_FragColor[0] * 255;
                            frame_buffer.color_buffer[fb_indx + 1] = processed_fragment.gl_FragColor[1] * 255;
                            frame_buffer.color_buffer[fb_indx + 2] = processed_fragment.gl_FragColor[2] * 255;
                            frame_buffer.color_buffer[fb_indx + 3] = processed_fragment.gl_FragColor[3] * 255;

                        }

                } // Fragment creation end
                // x+1

                counter ++;
                edge_value_1 -= edge_value_1_delta_y;
                edge_value_2 -= edge_value_2_delta_y;
                edge_value_3 -= edge_value_3_delta_y;

            } // x-row end
            // y+1
            edge_value_1 += (counter * edge_value_1_delta_y);
            edge_value_2 += (counter * edge_value_2_delta_y);
            edge_value_3 += (counter * edge_value_3_delta_y);


            edge_value_1 += edge_value_1_delta_x;
            edge_value_2 += edge_value_2_delta_x;
            edge_value_3 += edge_value_3_delta_x;

        } // y-column end
    } // Pined's algorithm end

}

/// @}
