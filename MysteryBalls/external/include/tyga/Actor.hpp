/**
 @file      Actor.hpp
 @author    Tyrone Davison
 @date      October 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_ACTOR__
#define __TYGA_ACTOR__

#include "Matrix.hpp"
#include <memory>
#include <unordered_set>

namespace tyga
{

class ActorComponent;
class ActorDelegate;
class ActorWorld;

class Actor : public std::enable_shared_from_this<Actor>
{
public:

    Actor();

#pragma region Transformation Property

    Matrix4x4
    Transformation() const;

    void
    setTransformation(Matrix4x4 m);

#pragma endregion

#pragma region World Property

    std::shared_ptr<ActorWorld>
    World() const;

    void // NB: for internal use only
    setWorld(std::weak_ptr<ActorWorld> w);

    void // NB: for internal use only
    setNullWorld();

#pragma endregion

#pragma region Delegate Property

    std::shared_ptr<ActorDelegate>
    Delegate() const;

    void
    setDelegate(std::shared_ptr<ActorDelegate> d);

#pragma endregion

#pragma region Component Management

    void
    attachComponent(std::shared_ptr<ActorComponent> c);

    void
    detachComponent(std::shared_ptr<ActorComponent> c);

#pragma endregion

#pragma region Priority Property

    int
    Priority() const;

    void
    setPriority(int priority);

#pragma endregion

    // TODO: Id property

    // TODO: Enabled property

private:
    std::weak_ptr<ActorWorld> world_;
    Matrix4x4 xform_;
    std::shared_ptr<ActorDelegate> delegate_;
    std::unordered_set<std::shared_ptr<ActorComponent>> components_;
    int priority_;
};

class ActorComponent : public std::enable_shared_from_this<ActorComponent>
{
public:
    std::shared_ptr<Actor>
    Actor() const;

    void // NB: for internal use only
    setActor(std::weak_ptr<tyga::Actor> actor);

    void // NB: for internal use only
    setNullActor();

private:
    std::weak_ptr<tyga::Actor> actor_;
};

} // end namespace tyga

#endif
