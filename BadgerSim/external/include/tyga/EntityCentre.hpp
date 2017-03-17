/**
 @file      EntityCentre.hpp
 @author    Tyrone Davison
 @date      February 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_ENTITY_CENTRE__
#define __TYGA_ENTITY_CENTRE__

#include "RunloopTaskProtocol.hpp"
#include <memory>
#include <set>

namespace tyga
{

class EntityDelegate;

class EntityCentre : public RunloopTaskProtocol
{
public:

    static std::shared_ptr<EntityCentre>
    defaultCentre();

    EntityCentre();

    ~EntityCentre();

    void
    addEntityWithDelegate(std::shared_ptr<EntityDelegate>);

    void
    removeEntityWithDelegate(std::shared_ptr<EntityDelegate>);

private:

    void
    runloopWillBegin();

    void
    runloopExecuteTask();

    void
    runloopDidEnd();

    static std::shared_ptr<EntityCentre> default_centre_;

    std::set<std::shared_ptr<EntityDelegate>> entities_;

};

} // end namespace tyga

#endif
