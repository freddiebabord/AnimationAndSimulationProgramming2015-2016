#include "MyUtils.hpp"
#include <tyga\Actor.hpp>
#include <math.h>
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <iostream>


namespace FB
{

	tyga::Matrix4x4 translate(float x, float y, float z)
	{
		return tyga::Matrix4x4(       1,       0,       0,       0,
									  0,       1,       0,       0,
									  0,       0,       1,       0,
									  x,       y,       z,       1);
	}

	tyga::Matrix4x4 translate(tyga::Vector3 pos)
	{
		return tyga::Matrix4x4(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			pos.x, pos.y, pos.z, 1);
	}

	tyga::Matrix4x4 rotateX(float deg)
	{
		float angle = degToRad(deg);
		float c = cos(angle);
		float s = sin(angle);
		return tyga::Matrix4x4( 1, 0, 0, 0,
							    0, c, s, 0,
								0, -s, c, 0,
								0, 0, 0, 1);
	}

	tyga::Matrix4x4 rotateY(float deg)
	{
		float angle = degToRad(deg);
		float c = cos(angle);
		float s = sin(angle);
		return tyga::Matrix4x4( c, 0, -s, 0,
							    0, 1, 0, 0,
								s, 0, c, 0,
								0, 0, 0, 1);
	}

	tyga::Matrix4x4 rotateZ(float deg)
	{
		float angle = degToRad(deg);
		float c = cos(angle);
		float s = sin(angle);
		return tyga::Matrix4x4( c,		s,		0,		0,
							   -s,		c,		0,		0,
								0,		0,		1,		0,
								0,		0,		0,		1);
	}

	tyga::Matrix4x4 rotate(float X, float Y, float Z)
	{
		auto r = rotateX(X);
		auto g = rotateY(Y);
		auto b = rotateZ(Z);
		return r * g * b;
	}

	tyga::Matrix4x4 rotate(tyga::Vector3 pos)
	{
		auto r = rotateX(pos.x);
		auto g = rotateY(pos.y);
		auto b = rotateZ(pos.z);
		return r * g * b;
	}

	tyga::Matrix4x4 scale(float scale)
	{
		return tyga::Matrix4x4( 1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, scale);
	}

	tyga::Vector3 Lerp(tyga::Vector3 a, tyga::Vector3 b, float s)
	{
		float x = (a.x * (1 - s) + b.x * s);
		float y = (a.y * (1 - s) + b.y * s);
		float z = (a.z * (1 - s) + b.z * s);
		return tyga::Vector3(x, y, z);
	}

	tyga::Matrix4x4 Frenet(const tyga::Vector3& pos, const tyga::Vector3& dir, const tyga::Vector3& up)
	{
		const tyga::Vector3 W = tyga::unit(dir);
		tyga::Vector3 U = tyga::cross(up, W);
		const tyga::Vector3 V = tyga::cross(W, U);
		U = tyga::cross(V, W);

		return tyga::Matrix4x4(	U.x, U.y, U.z, 0,
								V.x, V.y, V.z, 0,
								W.x, W.y, W.z, 0,
								pos.x, pos.y, pos.z, 1);

	}

	/*tyga::Matrix4x4 Frenet(BezierCurve curve, const float time, const tyga::Vector3 upDirection)
	{
		const tyga::Vector3 pos = curve.Solve(time);
		const tyga::Vector3 W = tyga::unit(-curve.SolveTangent(time));
		tyga::Vector3 U = tyga::cross(upDirection, W);
		const tyga::Vector3 V = tyga::cross(W, U);
		U = tyga::cross(V, W);

		return tyga::Matrix4x4(U.x, U.y, U.z, 0,
			V.x, V.y, V.z, 0,
			W.x, W.y, W.z, 0,
			pos.x, pos.y, pos.z, 1);

	}*/

	tyga::Matrix4x4 QuaternionToMatrix(const tyga::Quaternion& quaternion)
	{
		const float x = quaternion.x;
		const float y = quaternion.y;
		const float z = quaternion.z;
		const float w = quaternion.w;

		float xx = 1 - 2 *y*y - 2 * z*z;
		float xy = 2 * x*y - 2 * w*z;
		float xz = 2 * x*z + 2 * w*y;

		float yx = 2 * x*y + 2 * w*z;
		float yy = 1 - 2 * x*x -2 * z*z;
		float yz = 2 * y*z - 2 * w*x;

		float zx = 2 * x*z - 2 * w*y;
		float zy = 2 * y*z + 2 * w*x;
		float zz = 1 - 2 * x*x - 2 * y*y;

		return tyga::Matrix4x4(xx, yx, zx, 0,
								xy, yy, zy, 0,
								xz, yz, zz, 0,
								0, 0, 0, 1);
	}

	tyga::Quaternion SLerp(tyga::Quaternion a, tyga::Quaternion b, float s)
	{
		float dotProd = a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;

		auto theta = acos(dotProd);
		return (sin((1 - s)*theta) / sin(theta)) * a + ((sin(s*theta)) / sin(theta)) * b;
	}

#pragma region BezierCurve

	

#pragma endregion

#pragma region Hierarchy

	

#pragma endregion

#pragma region SuperAnimator

	Animator::Animator()
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::AddAnimation(const Animation anim)
	{
		animations.push_back(anim);
	}

	tyga::Matrix4x4 Animator::Solve(float time)
	{
		if (animations[currentAnimation].endTime <= time)
			currentAnimation++;
		if (currentAnimation < (int)animations.size())
			return animations[currentAnimation].Solve(time);
		else
			return animations[currentAnimation-1].Solve(time);
	}

#pragma endregion
}
