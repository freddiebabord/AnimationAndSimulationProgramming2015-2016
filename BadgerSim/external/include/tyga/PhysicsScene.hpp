/**
 @file      PhysicsScene.hpp
 @author    Tyrone Davison
 @date      February 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_PHYSICS_SCENE__
#define __TYGA_PHYSICS_SCENE__

#include "Matrix.hpp"
#include "Vector.hpp"
#include <memory>
#include <list>

namespace tyga
{

struct PhysicsCollision
{
    Vector3 position; // position of touch
    float depth; // depth of penetration now
    Vector3 normal; // direction of touch
    float time; // time of touch

    PhysicsCollision();
};

struct PhysicsObject
{
    Vector3 position;
    Vector3 velocity;
    float mass;
    Vector3 force;
    std::list<PhysicsCollision> collisions;

    PhysicsObject();
};

struct PhysicsPlane : public PhysicsObject
{
    Vector3 position;
    Vector3 normal;
    float radius; // practical option to limit effect of plane

    PhysicsPlane();
};

struct PhysicsSphere : public PhysicsObject
{
    Vector3 position;
    float radius;

    PhysicsSphere();
};

struct PhysicsBox : public PhysicsObject
{
    Matrix4x4 xform;

    PhysicsBox();
};

class PhysicsScene
{
public:

    static std::shared_ptr<PhysicsScene>
    defaultScene();

    PhysicsScene();

    ~PhysicsScene();

    void
    pruneDeadObjects();

    int
    numberOfObjects() const;

    std::weak_ptr<PhysicsObject>
    object(int index) const;

    std::shared_ptr<PhysicsPlane>
    newPlane();

    int
    numberOfPlanes() const;

    std::weak_ptr<PhysicsPlane>
    plane(int index) const;

    std::shared_ptr<PhysicsSphere>
    newSphere();

    int
    numberOfSpheres() const;

    std::weak_ptr<PhysicsSphere>
    sphere(int index) const;

    std::shared_ptr<PhysicsBox>
    newBox();

    int
    numberOfBoxes() const;

    std::weak_ptr<PhysicsBox>
    box(int index) const;

private:

    static std::shared_ptr<PhysicsScene> default_scene_;

    std::list<std::weak_ptr<PhysicsPlane>> planes_;
    std::list<std::weak_ptr<PhysicsSphere>> spheres_;
    std::list<std::weak_ptr<PhysicsBox>> boxes_;

};

} // end namespace tyga

#endif
