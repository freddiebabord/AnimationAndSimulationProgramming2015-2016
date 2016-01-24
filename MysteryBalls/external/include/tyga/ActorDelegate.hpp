/**
 @file      ActorDelegate.hpp
 @author    Tyrone Davison
 @date      November 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_ACTOR_DELEGATE__
#define __TYGA_ACTOR_DELEGATE__

#include <memory>

namespace tyga
{

class Actor;
class ActorWorld;

class ActorDelegate : public std::enable_shared_from_this<ActorDelegate>
{
public:
    ActorDelegate();

    std::shared_ptr<tyga::Actor>
    Actor() const;

    void // NB: for internal use only
    setActor(std::weak_ptr<tyga::Actor> actor);

    void
    addToWorld(std::shared_ptr<ActorWorld> world);

    void
    removeFromWorld();

public:
    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) {}

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) {}

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) {}

private:
    std::weak_ptr<tyga::Actor> actor_;
};

} // end namespace tyga

#endif
