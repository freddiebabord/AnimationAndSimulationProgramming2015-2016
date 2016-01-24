/**
 @file      ApplicationDelegate.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_APPLICATION_DELEGATE__
#define __TYGA_APPLICATION_DELEGATE__

#include <memory>

namespace tyga
{

class InputStateProtocol;

class ApplicationDelegate
{
public:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed) {}

    virtual void
    applicationDidStart() {}

    virtual void
    applicationRunloopWillBegin() {}

    virtual void
    applicationRunloopDidEnd() {}

    virtual void
    applicationWillStop() {}

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state) {}

};

} // end namespace tyga

#endif
