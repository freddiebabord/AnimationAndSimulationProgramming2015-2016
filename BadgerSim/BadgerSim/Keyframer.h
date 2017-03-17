#pragma once
#include <tyga/Math.hpp>
#include <vector>
#include "BezierCurve.h"
namespace FB{



	template <typename Type, typename Key>
	class Keyframe
	{
	public:
		Keyframe<Type, Key>(){};
		Keyframe<Type, Key>(Key param_, Type value_)
		{
			key = param_;
			value = value_;
		};

		Key key;
		Type value;
	};

	typedef float(*stepPtr)(float, float, float);
	typedef float(*lerpPtr)(FB::CombinedParam, FB::CombinedParam, float);
	typedef float(*basicFuncPtr)(CombinedParam);

	// Type: The data type of the keyframe
	// StepType: liner or smooth step
	// Lerp Type: LERP or SLERP
	// BasicFunction: Translation / rotate etc.
	template <typename Type, typename Key/*, typename ReturnType, stepPtr StepType, lerpPtr LerpType, basicFuncPtr BasicFunction*/>
	class Keyframer
	{
	public:
		Keyframer<Type, Key/*, ReturnType, StepType, LerpType, BasicFunction*/>(){};
		~Keyframer<Type, Key/*, ReturnType, StepType, LerpType, BasicFunction*/>(){};

		void AddKey(Keyframe<Type, Key> value)
		{
			frames.push_back(value);
		};

		std::vector<Keyframe<Type, Key>>& GetKey() { return frames; };

		CombinedParam Solve(float time)
		{
			if (time <= frames.front().key)
			{
				return frames.front().value;
			}
			else if (time >= frames.back().key)
			{
				return frames.back().value;
			}
			else
			{
				int index = 1;
				while (time >= frames[index].key)
				{
					index++;
				}
				return frames[index].value;
			}
		}
	private:
		std::vector<Keyframe<Type, Key>> frames;
	};

}