/**
 @file      EntityDelegate.hpp
 @author    Tyrone Davison
 @date      February 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_ENTITY_DELEGATE__
#define __TYGA_ENTITY_DELEGATE__

namespace tyga
{

class EntityDelegate
{
public:

    virtual void
    entityWillActivate() {}

    virtual void
    entityDidDeactivate() {}

    virtual void
    entityLoopTick() {}

};

} // end namespace tyga

#endif
