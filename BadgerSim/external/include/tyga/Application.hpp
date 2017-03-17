/**
 @file      Application.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_APPLICATION__
#define __TYGA_APPLICATION__

#include <memory>
#include <cstdint>
#include <tygra/WindowViewDelegate.hpp>

namespace tyga
{

class ApplicationDelegate;
class RunloopTaskProtocol;

// TODO: document rendering could be concurrent to runloop
// TODO: warn about which methods are not thread safe
class Application
{
public:

    static void
    run(std::shared_ptr<ApplicationDelegate> delegate);

    static void
    addRunloopTask(std::shared_ptr<RunloopTaskProtocol> task);

    static void
    setRunloopFrequency(int frames_per_second);

    static void
    setWindowViewDelegate(std::shared_ptr<tygra::WindowViewDelegate> view);

    static uint64_t
    currentExecutionTimeInNanoSeconds();

private:
    static std::shared_ptr<class _Application> pimpl_;

};

} // end namespace tyga

#endif
