/**
 @file      GraphicsCentre.hpp
 @author    Tyrone Davison
 @date      October 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_GRAPHICS_CENTRE__
#define __TYGA_GRAPHICS_CENTRE__

#include "RunloopTaskProtocol.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Actor.hpp"
#include <memory>
#include <string>
#include <list>
#include <vector>

namespace tyga
{

struct GraphicsCamera : public ActorComponent
{
    Matrix4x4 xform; // depreciated: attach this to an Actor instead
    float near_plane_distance;
    float far_plane_distance;
    float vertical_field_of_view_radians;

protected:
    friend class GraphicsCentre;
    GraphicsCamera();
};

enum GraphicsLightType
{
    kGraphicsLightDirectional =1,
    kGraphicsLightPoint,
    kGraphicsLightSpot
};

struct GraphicsLight : public ActorComponent
{
    Matrix4x4 xform; // depreciated: attach this to an Actor instead
    Vector3 colour;
    float intensity;
    float range;
    float cone_radians;
    GraphicsLightType type;

protected:
    friend class GraphicsCentre;
    GraphicsLight();
};

enum GraphicsMaterialType
{
    kGraphicsMaterialLambert =1,
    kGraphicsMaterialPhong
};

struct GraphicsMaterial
{
    Vector3 colour;
    float alpha;
    GraphicsMaterialType type;
    std::string texture;

protected:
    friend class GraphicsCentre;
    GraphicsMaterial();

    int current_index; /* for internal use only */
};

//struct GraphicsMaterialEx;

struct GraphicsMeshVertex
{
    Vector3 position;
    Vector3 normal;
    Vector3 tangent;
    Vector2 texcoord;
};

class GraphicsMeshDelegate
{
public: // note const expectation

    virtual int
    graphicsMeshElementCount() const =0;

    virtual int
    graphicsMeshVertexCount() const =0;

    virtual void
    graphicsMeshGenerate(tyga::GraphicsMeshVertex vertex_array[],
                         unsigned int element_array[]) const =0;
};

struct GraphicsMesh;

struct GraphicsModel : public ActorComponent
{
    Matrix4x4 xform; // depreciated: attach this to an Actor instead
    std::shared_ptr<GraphicsMesh> mesh;
    std::shared_ptr<GraphicsMaterial> material;

protected:
    friend class GraphicsCentre;
    GraphicsModel();
};

struct GraphicsSpriteVertex
{
    Vector3 position;
    float size;
    Vector3 colour;
    float alpha;
    float rotation;
};

class GraphicsSpriteDelegate
{
public: // note const expectation

    virtual std::string
    graphicsSpriteTexture() const =0;

    virtual int
    graphicsSpriteVertexCount() const =0;

    virtual void
    graphicsSpriteGenerate(tyga::GraphicsSpriteVertex vertex_array[]) const =0;
    // note this is a raw pointer, do not retain

};

struct GraphicsSprite;

class GraphicsSceneProtocol;
class GraphicsScene;

class GraphicsCentre : public RunloopTaskProtocol
{
public:

    static std::shared_ptr<GraphicsCentre>
    defaultCentre(); // not thread safe

public:
    GraphicsCentre();

    ~GraphicsCentre();

    std::shared_ptr<GraphicsSceneProtocol>
    scene() const; // deep copy

    std::shared_ptr<GraphicsCamera>
    newCamera();

    std::shared_ptr<GraphicsLight>
    newLight();

    std::shared_ptr<GraphicsMaterial>
    newMaterial();
    
    std::shared_ptr<GraphicsMesh>
    newMeshWithIdentifier(std::string identifier);

    std::shared_ptr<GraphicsMesh>
    newMeshWithData(std::vector<GraphicsMeshVertex>&& vertex_array,
                    std::vector<unsigned int>&& element_array); // recommend use std::move

    std::shared_ptr<GraphicsMesh>
    newMeshWithDelegate(std::shared_ptr<GraphicsMeshDelegate> delegate);

    std::shared_ptr<GraphicsModel>
    newModel();

    std::shared_ptr<GraphicsSprite>
    newSpriteWithDelegate(std::shared_ptr<GraphicsSpriteDelegate> delegate);

private:

    void
    runloopWillBegin();

    void
    runloopExecuteTask();

    void
    runloopDidEnd();

    static std::string
    randomIdentifier();

    static std::shared_ptr<GraphicsCentre> default_centre_;

    std::list<std::weak_ptr<GraphicsCamera>> cameras_;
    std::list<std::weak_ptr<GraphicsLight>> lights_;
    std::list<std::weak_ptr<GraphicsMaterial>> materials_;
    std::list<std::weak_ptr<GraphicsMesh>> meshes_;
    std::list<std::weak_ptr<GraphicsModel>> models_;
    std::list<std::weak_ptr<GraphicsSprite>> sprites_;

    std::shared_ptr<GraphicsScene> current_scene_;

};

} // end namespace tyga

#endif
