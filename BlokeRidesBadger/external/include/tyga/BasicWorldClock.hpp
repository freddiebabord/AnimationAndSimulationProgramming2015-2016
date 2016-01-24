/**
 @file      BasicWorldClock.hpp
 @author    Tyrone Davison
 @date      October 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_BASIC_WORLD_CLOCK__
#define __TYGA_BASIC_WORLD_CLOCK__

namespace tyga
{

class BasicWorldClock
{
public:

    static void
    update();

    static float
    CurrentTime();

    static float
    CurrentTickInterval();

private:

    static float time_;
    static float dt_;

};

} // end namespace tyga

#endif
