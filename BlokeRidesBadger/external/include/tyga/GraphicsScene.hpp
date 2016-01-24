/**
 @file      GraphicsScene.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_GRAPHICS_SCENE__
#define __TYGA_GRAPHICS_SCENE__

#include "GraphicsSceneProtocol.hpp"
#include <memory>
#include <vector>

// TODO: document me

namespace tyga
{

/*
struct GraphicsSceneMeshEx : public GraphicsSceneMesh
{
    std::string identifier;
};
*/

class GraphicsScene : public GraphicsSceneProtocol
{
public:

    std::vector<GraphicsSceneCamera> cameras_;
    std::vector<GraphicsSceneLight> lights_;
    std::vector<GraphicsSceneMaterial> materials_;
    std::vector<GraphicsSceneMesh> meshes_;
    std::vector<GraphicsSceneModel> models_;
    std::vector<GraphicsSceneSprite> sprites_;

    GraphicsScene();

    ~GraphicsScene();

private:

    int
    numberOfCameras() const;

    GraphicsSceneCamera
    camera(int index) const;

	int
    numberOfLights() const;

	GraphicsSceneLight
    light(int index) const;

	int
    numberOfMaterials() const;

	GraphicsSceneMaterial
    material(int index) const;

    int
    numberOfMeshes() const;

    bool
    meshIsDynamic(int index) const;

    std::string
    meshIdentifier(int index) const;

    bool
    meshDataIsReady(int index) const;

    GraphicsSceneMesh
    mesh(int index) const; // warn of performance issues (loads geom if not available)

    int
    numberOfModels() const;

	GraphicsSceneModel
    model(int index) const;

    int
    numberOfSprites() const;

    bool
    spriteDataIsReady(int index) const;

    GraphicsSceneSprite
    sprite(int index) const;

};

} // end namespace tyga

#endif
