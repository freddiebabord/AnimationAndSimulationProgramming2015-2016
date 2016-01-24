/**
 @file      Math.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_MATH__
#define __TYGA_MATH__

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

// repeat because something is preventing the macro working
#if !defined (_MATH_DEFINES_DEFINED)
#define _MATH_DEFINES_DEFINED

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

#endif  /* !defined (_MATH_DEFINES_DEFINED) */


// TODO: document me

namespace tyga
{

float
dot(Vector2, Vector2);

float
length(Vector2);

Vector2
unit(Vector2);

Vector2
operator-(Vector2);

Vector2
operator+(Vector2, Vector2);

Vector2
operator-(Vector2, Vector2);

Vector2
operator*(float, Vector2);

Vector2
operator*(Vector2, float);

Vector2
operator/(Vector2, float);

Vector2
operator+=(Vector2&, Vector2);

Vector2
operator-=(Vector2&, Vector2);

Vector2
operator*=(Vector2&, float);

Vector2
operator/=(Vector2&, float);

float
dot(Vector3, Vector3);

float
length(Vector3);

Vector3
unit(Vector3);

Vector3
operator-(Vector3);

Vector3
operator+(Vector3, Vector3);

Vector3
operator-(Vector3, Vector3);

Vector3
operator*(float, Vector3);

Vector3
operator*(Vector3, float);

Vector3
operator/(Vector3, float);

Vector3
operator+=(Vector3&, Vector3);

Vector3
operator-=(Vector3&, Vector3);

Vector3
operator*=(Vector3&, float);

Vector3
operator/=(Vector3&, float);

Vector3
cross(Vector3, Vector3);

Vector3
standardize(Vector4);

Vector3
truncate(Vector4);

Vector4
operator*(Vector4, Matrix4x4);

Vector4
operator*(Matrix4x4, Vector4);

Matrix4x4
inverse(Matrix4x4);

Matrix4x4
transpose(Matrix4x4);

Matrix4x4
operator*=(Matrix4x4&, Matrix4x4);

Matrix4x4
operator+=(Matrix4x4&, Matrix4x4);

Matrix4x4
operator-=(Matrix4x4&, Matrix4x4);

Matrix4x4
operator*=(Matrix4x4&, float);

Matrix4x4
operator*(Matrix4x4, Matrix4x4);

Matrix4x4
operator*(Matrix4x4, float);

Matrix4x4
operator*(float, Matrix4x4);

Matrix4x4
operator+(Matrix4x4, Matrix4x4);

Matrix4x4
operator-(Matrix4x4, Matrix4x4);

float
norm(Quaternion);

Quaternion
conjugate(Quaternion);

Quaternion
inverse(Quaternion);

Quaternion
unit(Quaternion);

Quaternion
operator-(Quaternion);

Quaternion
operator+(Quaternion, Quaternion);

Quaternion
operator-(Quaternion, Quaternion);

Quaternion
operator*(Quaternion, Quaternion);

Quaternion
operator*(float, Quaternion);

Quaternion
operator*(Quaternion, float);

Quaternion
operator/(Quaternion, float);

Quaternion
operator+=(Quaternion&, Quaternion);

Quaternion
operator-=(Quaternion&, Quaternion);

Quaternion
operator*=(Quaternion&, Quaternion);

Quaternion
operator*=(Quaternion&, float);

Quaternion
operator/=(Quaternion&, float);

} // end namespace tyga

#endif
