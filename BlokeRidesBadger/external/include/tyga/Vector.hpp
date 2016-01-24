/**
 @file      Vector.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_VECTOR__
#define __TYGA_VECTOR__

namespace tyga
{

class Vector2
{
public:

    Vector2();

    Vector2(float V0, float V1);

    union
    {
        float v[2];
        struct
        {
            float x, y;
        };
        struct
        {
            float s, t;
        };
    };

};

class Vector3
{
public:

    Vector3();

    Vector3(float V0, float V1, float V2);

    Vector3(Vector2 V01, float V2);

    union
    {
        float v[3];
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
        struct
        {
            float s, t, r;
        };
    };

};

class Vector4
{
public:

    Vector4();

    Vector4(float V0, float V1, float V2, float V3);

    Vector4(Vector2 V01, float V2, float V3);

    Vector4(Vector3 V012, float V3);

    union
    {
        float v[4];
        struct
        {
            float x, y, z, w;
        };
    };

};

} // end namespace tyga

#include "Vector.inl"

#endif
