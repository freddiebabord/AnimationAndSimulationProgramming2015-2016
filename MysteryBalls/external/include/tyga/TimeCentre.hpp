/**
 @file      TimeCentre.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_TIME_CENTRE__
#define __TYGA_TIME_CENTRE__

#include "RunloopTaskProtocol.hpp"
#include <memory>
#include <chrono>
#include <list>

namespace tyga
{

class TimeListener;

class TimeCentre : public std::enable_shared_from_this<TimeCentre>,
                   public RunloopTaskProtocol
{
public:

    static std::shared_ptr<TimeCentre>
    defaultCentre();

    TimeCentre();

    ~TimeCentre();

    void
    setMonotonicClock(std::chrono::milliseconds period);

    // NOTE: can't be sooner than next frame

    void
    addRepeatListener(std::shared_ptr<TimeListener> listener,
                      std::chrono::milliseconds period, // zero will give once per frame
                      int user_data);

    void
    removeRepeatListener(std::shared_ptr<TimeListener> listener);

    void
    callListenerAtTime(std::shared_ptr<TimeListener> listener,
                       std::chrono::milliseconds time,
                       int user_data);

    void
    callListenerAfterDelay(std::shared_ptr<TimeListener> listener,
                           std::chrono::milliseconds delay, // zero will be next frame
                           int user_data);

    void
    cancelListenerCall(std::shared_ptr<TimeListener> listener);

    std::chrono::milliseconds
    currentTime() const;

    std::chrono::milliseconds
    periodSincePreviousFrame() const;

    std::chrono::milliseconds
    periodUntilNextFrame() const;

private:

    void
    runloopWillBegin();

    void
    runloopExecuteTask();

    void
    runloopDidEnd();

    static std::shared_ptr<TimeCentre> default_centre_;

    struct Listener
    {
        std::shared_ptr<TimeListener> listener;
        std::chrono::milliseconds time_to_call;
        std::chrono::milliseconds repeat_period;
        int user_data;
    };

    // TODO: upgrade to an improved, sorted container
    std::list<Listener> listeners_;

    //std::chrono::system_clock::time_point start_time_;
    std::chrono::milliseconds now_;
    std::chrono::milliseconds previous_;
    std::chrono::milliseconds period_;

};

} // end namespace tyga

#endif
