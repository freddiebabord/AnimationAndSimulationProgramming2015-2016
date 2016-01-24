/**
 @file      Matrix.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_MATRIX__
#define __TYGA_MATRIX__

namespace tyga
{

class Matrix4x4
{
public:

    Matrix4x4();

    Matrix4x4(float M00, float M01, float M02, float M03,
              float M10, float M11, float M12, float M13,
              float M20, float M21, float M22, float M23,
              float M30, float M31, float M32, float M33);

    union
    {
        float m[4][4];
        struct
        {
            float _00, _01, _02, _03;
            float _10, _11, _12, _13;
            float _20, _21, _22, _23;
            float _30, _31, _32, _33;
        };
    };

};

/*
class Matrix4x3
{
public:

    Matrix4x3();

    Matrix4x3(float M00, float M01, float M02,
              float M10, float M11, float M12,
              float M20, float M21, float M22,
              float M30, float M31, float M32);

    union
    {
        float m[4][3];
        struct
        {
            float _00, _01, _02;
            float _10, _11, _12;
            float _20, _21, _22;
            float _30, _31, _32;
        };
    };

};
*/

} // end namespace tyga

#include "Matrix.inl"

#endif
