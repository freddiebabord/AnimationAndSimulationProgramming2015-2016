/**
 @file      SceneTime.hpp
 @author    Tyrone Davison
 @date      February 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_SCENE_TIME__
#define __TYGA_SCENE_TIME__

namespace tyga
{

class SceneTime
{
public:

    static void
    update();

    static float
    currentTime();

    static float
    durationOfPreviousLoop();

private:

    static float time_;
    static float dt_;

};

} // end namespace tyga

#endif
