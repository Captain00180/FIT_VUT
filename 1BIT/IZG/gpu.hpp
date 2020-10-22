/*!
 * @file
 * @brief This file contains class that represents graphic card.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * Vypracoval Filip Januška
 */
#pragma once

#include <student/fwd.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
#include <cmath>

/**
 * @brief Buffer structure
 */
class Buffer {
public:
    BufferID ID;
    uint64_t size;      ///< size of allocated memory block
    void * data;    ///< pointer to allocated memory block
};

// Vertex Puller Class
class VertexPuller {
public:
    struct Indexing_t {
        IndexType type;
        BufferID indexing_id;
    };
    struct PullerHead_t {
        bool enabled;
        BufferID id;
        AttributeType type;
        uint64_t stride;
        uint64_t offset;
    };

    VertexPullerID ID;
    Indexing_t indexing;
    PullerHead_t pullerheads [maxAttributes];

};

// Shader Program Class
class ShaderProgram {
public:
    ProgramID ID;
    VertexShader vert_shader;
    FragmentShader frag_shader;
    Uniforms uniforms;
    AttributeType attribs[maxAttributes];
    Attribute attrib;


};

class FrameBuffer {
public:
    bool created = false;
    uint32_t width;
    uint32_t height;

    float * depth_buffer;
    uint8_t * color_buffer;
};

struct Triangle {
    OutVertex vertices[3];
};

/**
 * @brief This class represent software GPU
 */
class GPU{
  public:
    GPU();
    virtual ~GPU();

    //buffer object commands
    BufferID  createBuffer           (uint64_t size);
    void      deleteBuffer           (BufferID buffer);
    void      setBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void const* data);
    void      getBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void      * data);
    bool      isBuffer               (BufferID buffer);

    //vertex array object commands (vertex puller)
    ObjectID  createVertexPuller     ();
    void      deleteVertexPuller     (VertexPullerID vao);
    void      setVertexPullerHead    (VertexPullerID vao,uint32_t head,AttributeType type,uint64_t stride,uint64_t offset,BufferID buffer);
    void      setVertexPullerIndexing(VertexPullerID vao,IndexType type,BufferID buffer);
    void      enableVertexPullerHead (VertexPullerID vao,uint32_t head);
    void      disableVertexPullerHead(VertexPullerID vao,uint32_t head);
    void      bindVertexPuller       (VertexPullerID vao);
    void      unbindVertexPuller     ();
    bool      isVertexPuller         (VertexPullerID vao);

    //program object commands
    ProgramID createProgram          ();
    void      deleteProgram          (ProgramID prg);
    void      attachShaders          (ProgramID prg,VertexShader vs,FragmentShader fs);
    void      setVS2FSType           (ProgramID prg,uint32_t attrib,AttributeType type);
    void      useProgram             (ProgramID prg);
    bool      isProgram              (ProgramID prg);
    void      programUniform1f       (ProgramID prg,uint32_t uniformId,float     const&d);
    void      programUniform2f       (ProgramID prg,uint32_t uniformId,glm::vec2 const&d);
    void      programUniform3f       (ProgramID prg,uint32_t uniformId,glm::vec3 const&d);
    void      programUniform4f       (ProgramID prg,uint32_t uniformId,glm::vec4 const&d);
    void      programUniformMatrix4f (ProgramID prg,uint32_t uniformId,glm::mat4 const&d);

    //framebuffer functions
    void      createFramebuffer      (uint32_t width,uint32_t height);
    void      deleteFramebuffer      ();
    void      resizeFramebuffer      (uint32_t width,uint32_t height);
    uint8_t*  getFramebufferColor    ();
    float*    getFramebufferDepth    ();
    uint32_t  getFramebufferWidth    ();
    uint32_t  getFramebufferHeight   ();

    //execution commands
    void      clear                  (float r,float g,float b,float a);
    void      drawTriangles          (uint32_t  nofVertices);

    //helpful functions
    float     edge_function         (OutVertex vert_A, OutVertex vert_B, double x, double y);
    float     max_of_3              (float a, float b, float c);
    float     min_of_3              (float a, float b, float c);
    template <typename att_type, typename flt>
    att_type  interpolate         (flt lambda_A, flt lambda_B, flt lambda_C, flt A_w, flt B_w, flt C_w, att_type A, att_type B, att_type C);
    float       cut_to_max            (float x, float y);
    float       cut_to_min            (float x, float y);



    /// \addtogroup gpu_init 00. proměnné, inicializace / deinicializace grafické karty
    /// @{
    /// \todo zde si můžete vytvořit proměnné grafické karty (buffery, programy, ...)
    /// @}


    // Vector of Buffers. Buffer IDs are practically their index in this vector
    std::vector<Buffer> buffer_arr;
    // Vector of empty Buffer IDs which can be assigned to new Buffers
    std::vector<BufferID> freeBufferID_arr;

    // Vector of Vertex Pullers. Their IDs represent their index in this vector
    std::vector< VertexPuller > vert_pull_arr;
    // Vector of free VP IDs which may be reused
    std::vector< VertexPullerID > freeVertID_arr;

    // Active Vertex Puller settings
    VertexPullerID active_vert_pull;

    // Vector of Shader Programs. Their IDs represent their index in this vector
    std::vector< ShaderProgram > shader_prog_arr;
    // Vector of free SP IDs which may be reused
    std::vector< ProgramID > freeProgID_arr;

    // Active Shader Program
    ProgramID active_shad_prog;

    // GPU FrameBuffer
    FrameBuffer frame_buffer;
};



