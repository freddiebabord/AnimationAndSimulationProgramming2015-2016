/**
 @file      ActorWorld.hpp
 @author    Tyrone Davison
 @date      October 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_ACTOR_WORLD__
#define __TYGA_ACTOR_WORLD__

#include "RunloopTaskProtocol.hpp"
#include <memory>
#include <list>

namespace tyga
{

class Actor;

class ActorWorld : public RunloopTaskProtocol,
                   public std::enable_shared_from_this<ActorWorld>
{
public:

    // TODO: should this be depreciated?
    static std::shared_ptr<ActorWorld>
    defaultWorld();

    ActorWorld();

    ~ActorWorld();

    void
    addActor(std::shared_ptr<Actor> a);

    void
    removeActor(std::shared_ptr<Actor> a);

    bool
    containsActor(std::shared_ptr<Actor> a);

    // TODO: find actor by id

private:

    void
    runloopWillBegin();

    void
    runloopExecuteTask();

    void
    runloopDidEnd();

    static std::shared_ptr<ActorWorld> default_centre_;

    std::list<std::shared_ptr<Actor>> actors_;

};

} // end namespace tyga

#endif
