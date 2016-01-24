/**
 @file      BasicRenderer.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_BASIC_RENDERER__
#define __TYGA_BASIC_RENDERER__

#include "GraphicsRendererProtocol.hpp"
#include <tgl/tgl.h>
#include <tygra/Image.hpp>
#include <unordered_map>

namespace tyga
{

class GraphicsSceneProtocol;

class BasicRenderer : public GraphicsRendererProtocol
{
public:

    BasicRenderer();

    ~BasicRenderer();

private:

    void
    setGraphicsScene(std::shared_ptr<tyga::GraphicsSceneProtocol> scene);

    void
    windowViewWillStart(std::shared_ptr<tygra::Window> window);

    void
    windowViewDidReset(std::shared_ptr<tygra::Window> window,
                       int width,
                       int height);

    void
    windowViewDidStop(std::shared_ptr<tygra::Window> window);

    void
    windowViewRender(std::shared_ptr<tygra::Window> window);

    std::shared_ptr<tyga::GraphicsSceneProtocol> scene_;

    struct ShaderProgram
    {
        GLuint vertex_shader;
        GLuint geometry_shader;
        GLuint fragment_shader;
        GLuint program;

        ShaderProgram() : vertex_shader(0),
                          geometry_shader(0),
                          fragment_shader(0),
                          program(0) {}
    };
    ShaderProgram basic_sp_;
    ShaderProgram sprite_sp_;

    static GLuint
    compileShader(GLenum type, std::string filepath);
    
    struct Mesh
    {
        GLuint vertex_vbo;
        GLuint index_vbo;
        GLuint vao;
        int element_count;

        Mesh() : vertex_vbo(0),
                 index_vbo(0),
                 vao(0),
                 element_count(0) {}
    };

    std::unordered_map<std::string, Mesh> meshes_;

    std::unordered_map<std::string, GLuint> textures_;

    static Mesh
    createMesh(const GraphicsSceneMesh&, bool stream_draw);

    Mesh
    loadMesh(std::string filepath);

    bool
    loadMeshes(std::string filepath);

    static Mesh
    combineMeshes(std::string filepath);

    static GLuint
    createTexture(const tygra::Image&);

    GLuint
    loadTexture(std::string filepath);

    bool
    loadTextures(std::string filepath);

};

} // end namespace tyga

#endif
