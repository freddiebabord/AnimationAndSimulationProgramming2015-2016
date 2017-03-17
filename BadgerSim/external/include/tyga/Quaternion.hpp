/**
 @file      Quaternion.hpp
 @author    Tyrone Davison
 @date      October 2013
 */

// TODO: document me

#pragma once
#ifndef __TYGA_QUATERNION__
#define __TYGA_QUATERNION__

#include "Vector.hpp"

namespace tyga
{

class Quaternion
{
public:

    Quaternion();

    Quaternion(float W, float X, float Y, float Z);

    Quaternion(float W, Vector3 V);

    union
    {
        float q[4];
        struct
        {
            float w, x, y, z;
        };
        struct
        {
            float w;
            Vector3 v;
        };
    };

};

}

#include "Quaternion.inl"

#endif
