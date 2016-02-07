#pragma once
#include <tyga/Math.hpp>
#include <tyga\ActorDelegate.hpp>
#include <vector>
#include <memory>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace FB
{
	class Animation
	{
	public:
		Animation();
		virtual ~Animation() {};

		virtual tyga::Matrix4x4 Solve(float time){ return tyga::Matrix4x4();  };
		float startTime = 0;
		float endTime = 0;
	};

	class BezierCurve;

	inline float Length(tyga::Vector3 a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	inline tyga::Vector3 Normalize(tyga::Vector3 a)
	{
		auto res = a;
		float length = Length(res);

		if (length != 0)
		{
			res.x = res.x / length;
			res.y = res.y / length;
			res.z = res.z / length;
		}

		return res;
	}

#pragma region Animation Basic

	//A 4x4 uniform translation matrix.
	tyga::Matrix4x4 translate(float x, float y, float z);

	tyga::Matrix4x4 translate(tyga::Vector3 pos);

	//A 4x4 rotation matrix about the Z-axis
	tyga::Matrix4x4 rotateZ(float deg);

	//A 4x4 rotation matrix about the X-axis
	tyga::Matrix4x4 rotateX(float deg);

	//A 4x4 rotation matrix about the Y-axis
	tyga::Matrix4x4 rotateY(float deg);

	//A 4x4 rotation matrix to resolve X Y and Z
	tyga::Matrix4x4 rotate(float X, float Y, float Z);

	//A 4x4 rotation matrix to resolve X Y and Z
	tyga::Matrix4x4 rotate(tyga::Vector3 pos);

	//A 4x4 scale matrix
	tyga::Matrix4x4 scale(float scale);

	tyga::Vector3 Lerp(tyga::Vector3 a, tyga::Vector3 b, float s);


	/*float GetParam(CombinedParam a)
	{
		return a.param;
	};*/

	tyga::Matrix4x4 Frenet(BezierCurve curve, const float time, const tyga::Vector3 upDirection = tyga::Vector3(0, 1, 0));

	tyga::Matrix4x4 Frenet(const tyga::Vector3& pos, const tyga::Vector3& dir, const tyga::Vector3& up);
	
	tyga::Matrix4x4 QuaternionToMatrix(const tyga::Quaternion& quaternion);

	tyga::Quaternion SLerp(tyga::Quaternion a, tyga::Quaternion b, float s);

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

#pragma endregion

#pragma region Template Functions

	//Convert from radians to degrees
	template<typename T>
	T radToDeg(T rad)
	{
		return (T)(rad * (180 / M_PI));
	}

	//Convert from dregrees to rads
	template<typename T>
	T degToRad(T deg)
	{
		return (T)(deg * (M_PI / 180));
	}

	//Oscilate and return a float
	template<typename T>
	T oscillate(T frequency, T amplitude)
	{
		return amplitude * sin(frequency);
	}	

	template<typename T>
	T Clamp(T in, T low, T high)
	{
		if (in <= low)
			return low;
		else if (in >= high)
			return high;
		else
			return in;
	};

	template <typename T>
	T linearstep(T min, T max, T val)
	{
		return Clamp((val - min) / (max - min), 0.f, 1.f);
	}

	template <typename T>
	T smoothStep(T min, T max, T val)
	{
		val = linearstep(min, max, val);
		return 3 * (val * val) - 2 * (val * val * val);
	}

	template <typename T>
	T smootherStep(T min, T max, T x)
	{
		// Scale, and clamp x to 0..1 range
		x = Clamp((x - min) / (max - min), (T)0.0, (T)1.0);
		// Evaluate polynomial
		return x*x*x*(x*(x * 6 - 15) + 10);
	}

	template <typename T>
	T Lerp(const T start, const T end, const float s)
	{
		return T(start * (1 - s) + end * s);
	}

	//Template for a continuous animation that requires an initial value and a rate of change of the same type which return the same type.
	template <typename T>
	T Continuous(T initialValue, T rateOfChange, float deltaTime)
	{
		return initialValue + rateOfChange * deltaTime;
	};

#pragma endregion

#pragma region SuperAnimator

	

	class Animator
	{
	public:
		Animator();
		~Animator();

		void AddAnimation(const Animation anim);
		tyga::Matrix4x4 Solve(float time);

	private:
		std::vector<Animation> animations;
		int currentAnimation = 0;
	};


#pragma endregion
}

