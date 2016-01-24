/**
 @file      RunloopTaskProtocol.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_RUNLOOP_TASK_PROTOCOL__
#define __TYGA_RUNLOOP_TASK_PROTOCOL__

namespace tyga
{

class RunloopTaskProtocol
{
public:

    virtual void
    runloopWillBegin() =0; // do private processing before entity interaction

    virtual void
    runloopExecuteTask() =0; // do processing in sync with entities

    virtual void
    runloopDidEnd() =0; // do processing after entity interaction

};

}

#endif
