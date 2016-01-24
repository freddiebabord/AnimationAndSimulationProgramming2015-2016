/**
 @file      TimeListener.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_TIME_LISTENER__
#define __TYGA_TIME_LISTENER__

#include <chrono>

namespace tyga
{

class TimeCentre;

class TimeListener
{
public:

    virtual void
    timeTick(std::shared_ptr<tyga::TimeCentre> time_centre,
             std::chrono::milliseconds time,
             int user_data) =0;

};

} // end namespace tyga

#endif
