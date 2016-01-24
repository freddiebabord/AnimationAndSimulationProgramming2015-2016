/**
 @file      InputState.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_INPUT_STATE__
#define __TYGA_INPUT_STATE__

// TODO: document me

#include "InputStateProtocol.hpp"

namespace tyga
{

class InputState : public InputStateProtocol
{
public:

    static const int MAX_GAMEPADS = 2;

    int keyboardKeyDownCount_[kInputKeyMaxEnum];
    float keyboardAxisPosition_[kInputKeyboardAxisMaxEnum];
    int mouseButtonDownCount_[kInputMouseButtonMaxEnum];
    float mouseAxisPosition_[kInputMouseAxisMaxEnum];
    int mouseCursorPosition_[kInputMouseAxisMaxEnum];
    int gamepadButtonDownCount_[MAX_GAMEPADS][kInputGamepadButtonMaxEnum];
    float gamepadAxisPosition_[MAX_GAMEPADS][kInputGamepadAxisMaxEnum];
    bool gamepadPresent_[MAX_GAMEPADS];

    InputState()
    {
        for (int& key : keyboardKeyDownCount_) {
            key = 0;
        }
        for (float& axis : keyboardAxisPosition_) {
            axis = 0.f;
        }
        for (int& button : mouseButtonDownCount_) {
            button = 0;
        }
        for (float& axis : mouseAxisPosition_) {
            axis = 0.f;
        }
        for (int& pos : mouseCursorPosition_) {
            pos = 0;
        }
        for (int pad = 0; pad < MAX_GAMEPADS; ++pad) {
            for (int& button : gamepadButtonDownCount_[pad]) {
                button = 0;
            }
        }
        for (int pad = 0; pad < MAX_GAMEPADS; ++pad) {
            for (float& axis : gamepadAxisPosition_[pad]) {
                axis = 0.f;
            }
        }
        for (int pad = 0; pad < MAX_GAMEPADS; ++pad) {
            gamepadPresent_[pad] = false;
        }
    }

    int
    keyboardKeyDownCount(int key_index) const override
    {
        // TODO: check index validity
        return keyboardKeyDownCount_[key_index];
    }

    float
    keyboardAxisPosition(int axis_index) const override
    {
        // TODO: check index validity
        return keyboardAxisPosition_[axis_index];
    }

    int
    mouseButtonDownCount(int button_index) const override
    {
        // TODO: check index validity
        return mouseButtonDownCount_[button_index];
    }

    float
    mouseAxisPosition(int axis_index) const override
    {
        // TODO: check index validity
        return mouseAxisPosition_[axis_index];
    }

    int
    mouseCursorPosition(int axis_index) const override
    {
        // TODO: check index validity
        return mouseCursorPosition_[axis_index];
    }

    int
    gamepadButtonDownCount(int gamepad_index,
                           int button_index) const override
    {
        // TODO: check index validity
        return gamepadButtonDownCount_[gamepad_index][button_index];
    }

    float
    gamepadAxisPosition(int gamepad_index,
                        int axis_index) const override
    {
        // TODO: check index validity
        return gamepadAxisPosition_[gamepad_index][axis_index];
    }

    bool
    gamepadPresent(int gamepad_index) const override
    {
        // TODO: check index validity
        return gamepadPresent_[gamepad_index];
    }

};

} // end namespace tyga

#endif
