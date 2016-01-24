/**
 @file      GraphicsSceneProtocol.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_GRAPHICS_SCENE_PROTOCOL__
#define __TYGA_GRAPHICS_SCENE_PROTOCOL__

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace tyga
{

struct GraphicsSceneCamera
{
    glm::mat4x3 xform;
    float near_plane_distance;
    float far_plane_distance;
    float vertical_field_of_view_radians;
};

enum GraphicsSceneLightType
{
	kGraphicsSceneLightUnknown =0,
	kGraphicsSceneLightDirectional,
	kGraphicsSceneLightPoint,
	kGraphicsSceneLightSpot
};

struct GraphicsSceneLight
{
    glm::mat4x3 xform;
	glm::vec3 colour;
	float intensity;
	float range;
	float cone_radians;
	GraphicsSceneLightType type;
};

enum GraphicsSceneMaterialType
{
	kGraphicsSceneMaterialUnknown =0,
	kGraphicsSceneMaterialLambert,
	kGraphicsSceneMaterialPhong
};

struct GraphicsSceneMaterial
{
	glm::vec3 colour;
    float alpha;
	GraphicsSceneMaterialType type;
    std::string texture;
};

struct GraphicsSceneMeshVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 texcoord;
};

struct GraphicsSceneMesh
{
    std::vector<GraphicsSceneMeshVertex> vertex_array;
    std::vector<unsigned int> element_array;
    std::string identifier;
    bool dynamic;

    GraphicsSceneMesh();
    GraphicsSceneMesh(GraphicsSceneMesh&&);
};

struct GraphicsSceneModel
{
	glm::mat4x3 xform;
	int mesh_index;
	int material_index;
};

struct GraphicsSceneSpriteVertex
{
    glm::vec3 position;
    float size;
    glm::vec3 colour;
    float alpha;
    float rotation;
};

struct GraphicsSceneSprite
{
    std::vector<GraphicsSceneSpriteVertex> vertex_array;
    std::string texture;

    GraphicsSceneSprite();
    GraphicsSceneSprite(GraphicsSceneSprite&&);
};

class GraphicsSceneProtocol
{
public:

    virtual int
    numberOfCameras() const =0;

    virtual tyga::GraphicsSceneCamera
    camera(int index) const =0;

	virtual int
    numberOfLights() const =0;

	virtual tyga::GraphicsSceneLight
    light(int index) const =0;

	virtual int
    numberOfMaterials() const =0;

	virtual tyga::GraphicsSceneMaterial
    material(int index) const =0;

    virtual int
    numberOfMeshes() const =0;
    
    virtual bool
    meshIsDynamic(int index) const =0;

    virtual std::string
    meshIdentifier(int index) const =0;

    virtual bool
    meshDataIsReady(int index) const =0;

    virtual tyga::GraphicsSceneMesh
    mesh(int index) const =0; // only callable once for a mesh (it moves the data)

    virtual int
    numberOfModels() const =0;

	virtual tyga::GraphicsSceneModel
    model(int index) const =0;

    virtual int
    numberOfSprites() const =0;

    virtual bool
    spriteDataIsReady(int index) const =0;

    virtual tyga::GraphicsSceneSprite
    sprite(int index) const =0; // only callable once

};

}

#endif
