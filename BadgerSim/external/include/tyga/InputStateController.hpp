/**
 @file      InputStateController.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_INPUT_STATE_CONTROLLER__
#define __TYGA_INPUT_STATE_CONTROLLER__

// TODO: document me

#include <memory>
#include <tygra/WindowControlDelegate.hpp>

namespace tyga
{

class InputState;

class InputStateController : public tygra::WindowControlDelegate
{
public:

    InputStateController();

    std::shared_ptr<InputState>
    staticState() const;

    void
    incrementFrameCounters();

private:

    void
    windowControlWillStart(std::shared_ptr<tygra::Window> window) override;

    void
    windowControlDidStop(std::shared_ptr<tygra::Window> window) override;

    void
    windowControlMouseMoved(std::shared_ptr<tygra::Window> window,
                            int x,
                            int y) override;		

    void
    windowControlMouseButtonChanged(std::shared_ptr<tygra::Window> window,
                                    int button_index,
                                    bool down) override;

    void
    windowControlMouseWheelMoved(std::shared_ptr<tygra::Window> window,
                                 int position) override;

    void
    windowControlKeyboardChanged(std::shared_ptr<tygra::Window> window,
                                 int key_index,
                                 bool down) override;

    void
    windowControlGamepadAxisMoved(std::shared_ptr<tygra::Window> window,
                                  int gamepad_index,
                                  int axis_index,
                                  float pos) override;

    void
    windowControlGamepadButtonChanged(std::shared_ptr<tygra::Window> window,
                                      int gamepad_index,
                                      int button_index,
                                      bool down) override;

    void
    windowControlGamepadPresenceChanged(std::shared_ptr<tygra::Window> window,
                                        int gamepad_index,
                                        bool present) override;

    std::shared_ptr<InputState> input_state_;
};


} // end namespace tyga

#endif
