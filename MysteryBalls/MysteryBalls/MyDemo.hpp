#pragma once

#include <tyga/ApplicationDelegate.hpp>
#include <tyga/GraphicsRendererProtocol.hpp>
#include "DominantBall.hpp"
#include "SlaveBall.hpp"
#include <random>

class MyDemo : public tyga::ApplicationDelegate
{
private:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed);

    virtual void
    applicationDidStart();

    virtual void
    applicationRunloopWillBegin();

    virtual void
    applicationRunloopDidEnd();

    virtual void
    applicationWillStop();

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state);

    void
    resetBalls();

    std::shared_ptr<tyga::GraphicsRendererProtocol> renderer_;

    std::shared_ptr<DominantBall> dominant_ball_;
    std::vector<std::shared_ptr<SlaveBall>> slave_balls_;

    std::minstd_rand rand;
    static const tyga::Vector2 MIN_BOUND;
    static const tyga::Vector2 MAX_BOUND;
};
