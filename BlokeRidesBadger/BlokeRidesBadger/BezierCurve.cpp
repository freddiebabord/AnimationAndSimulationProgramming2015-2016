#include "MyUtils.hpp"
#include "BezierCurve.h"

namespace FB{

	tyga::Vector3 BezierCurve::Solve(float time)
	{
		const float b0 = (1 - time) * (1 - time) * (1 - time);
		const float b1 = 3 * time * (1 - time) * (1 - time);
		const float b2 = 3 * time * time * (1 - time);
		const float b3 = time * time * time;
		tyga::Vector3 pos = path_[0] * b0 + path_[1] * b1 + path_[2] * b2 + path_[3] * b3;
		return pos;
	}

	tyga::Vector3 BezierCurve::SolveTangent(float time)
	{
		const float t0 = -3 * ((1 - time) * (1 - time));
		const float t1 = 3 * ((1 - time)*(1 - time)) - 6 * (1 - time)*time;
		const float t2 = 6 * (1 - time) * time - 3 * (time * time);
		const float t3 = 3 * (time * time);

		tyga::Vector3 dir = path_[0] * t0 + path_[1] * t1 + path_[2] * t2 + path_[3] * t3;
		return dir;
	}

	tyga::Vector3 BezierCurve::SolveCurvature(float time)
	{
		const float t0 = 6 - (6 * time);
		const float t1 = (18 * time) - 12;
		const float t2 = 6 - (18 * time);
		const float t3 = 6 * time;
		tyga::Vector3 dir = path_[0] * t0 + path_[1] * t1 + path_[2] * t2 + path_[3] * t3;
		return dir;
	}

	void CompositePath::AddCurve(BezierCurve bezierCurve)
	{
		curves.push_back(bezierCurve);
	}

	tyga::Matrix4x4 CompositePath::Animate(float time, int paramId)
	{
		if (time <= curves.front().GetParam().back())
		{
			auto anim_clip_phase_time = linearstep(curves.front().GetParam()[0], curves.front().GetParam()[curves.front().GetParam().size() - 1], time);
			tyga::Vector3 pos = curves.front().Solve(anim_clip_phase_time);
			tyga::Vector3 dir = curves.front().SolveTangent(anim_clip_phase_time);
			tyga::Vector3 up = curves.front().SolveCurvature(anim_clip_phase_time);
			return Frenet(pos, dir, tyga::Vector3(0, 1, 0));
		}
		else if (time >= curves.back().GetParam()[0])
		{
			auto anim_clip_phase_time = linearstep(curves.back().GetParam()[0], curves.back().GetParam()[curves.back().GetParam().size() - 1], time);
			tyga::Vector3 pos = curves.back().Solve(anim_clip_phase_time);
			tyga::Vector3 dir = curves.back().SolveTangent(anim_clip_phase_time);
			tyga::Vector3 up = curves.back().SolveCurvature(anim_clip_phase_time);
			return Frenet(pos, dir, tyga::Vector3(0, 1, 0));
		}
		else
		{
			int curveID = 1;
			int index = 1;
			while (time >= curves[curveID].GetParam()[index])
			{
				index++;
			}
			auto anim_clip_phase_time = linearstep(curves[curveID].GetParam().front(), curves[curveID].GetParam().back(), time);
			tyga::Vector3 pos = curves[curveID].Solve(anim_clip_phase_time);
			tyga::Vector3 dir = curves[curveID].SolveTangent(anim_clip_phase_time);
			tyga::Vector3 up = curves[curveID].SolveCurvature(anim_clip_phase_time);
			return Frenet(pos, dir, tyga::Vector3(0, 1, 0));
		}
	}

	tyga::Vector3 CompositePath::positionSolve(float time)
	{
		if (time <= 0)
		{
			auto anim_clip_phase_time = smootherStep<float>(curves.front().GetParam()[0], curves.front().GetParam()[curves.front().GetParam().size()-1], time);
			return curves.front().Solve(anim_clip_phase_time);
		}
		else if (time >= 1)
		{
			auto anim_clip_phase_time = smootherStep<float>(curves.back().GetParam()[0], curves.back().GetParam()[curves.front().GetParam().size()-1], time);
			return curves.back().Solve(anim_clip_phase_time);
		}
		else
		{
			int index = 1;
			while (time >= curves[index].GetParam()[curves.front().GetParam().size()])
			{
				index++;
			}
			int paramIdx = 0;
			while (time >= curves[index].GetParam()[paramIdx])
			{
				paramIdx++;
			}
			auto anim_clip_phase_time = smootherStep<float>(curves[index].GetParam()[paramIdx], curves[index].GetParam()[paramIdx], time);
			return curves[index].Solve(anim_clip_phase_time);
		}
	}

	tyga::Vector3 CompositePath::directionSolve(float time)
	{
		if (time <= 0)
		{
			auto a = curves.front().GetParam()[0];
			auto b = curves.front().GetParam()[curves.front().GetParam().size() - 1];
			auto anim_clip_phase_time = smootherStep<float>( a, b, time);
			return curves.front().SolveTangent(anim_clip_phase_time);
		}
		else if (time >= 1)
		{
			auto anim_clip_phase_time = smootherStep<float>(curves.back().GetParam()[0], curves.back().GetParam()[curves.front().GetParam().size()-1], time);
			return curves.back().SolveTangent(anim_clip_phase_time);
		}
		else
		{
			int index = 1;
			while (time >= curves[index].GetParam()[curves.front().GetParam().size()])
			{
				index++;
			}
			int paramIdx = 0;
			while (time >= curves[index].GetParam()[paramIdx])
			{
				paramIdx++;
			}
			auto anim_clip_phase_time = smootherStep<float>(curves[index].GetParam().front(), curves[index].GetParam().back(), time);
			return curves[index].SolveTangent(anim_clip_phase_time);
		}
	}

	tyga::Vector3 CompositePath::curvatureSolve(float time)
	{
		if (time <= 0)
		{
			auto a = curves.front().GetParam()[0];
			auto b = curves.front().GetParam()[curves.front().GetParam().size() - 1];
			auto anim_clip_phase_time = smootherStep<float>(a, b, time);
			return curves.front().SolveCurvature(anim_clip_phase_time);
		}
		else if (time >= 1)
		{
			auto anim_clip_phase_time = smootherStep<float>(curves.back().GetParam()[0], curves.back().GetParam()[curves.front().GetParam().size() - 1], time);
			return curves.back().SolveCurvature(anim_clip_phase_time);
		}
		else
		{
			int index = 0;
			if (time >= curves[index].GetParam()[curves.front().GetParam().size()-1])
			{
				index++;
			}
			int paramIdx = 0;
			if (time >= curves[index].GetParam()[paramIdx])
			{
				while (time >= curves[index].GetParam()[paramIdx])
				{
					paramIdx++;
				}
			}
			auto anim_clip_phase_time = smootherStep<float>(curves[index].GetParam().front(), curves[index].GetParam().back(), time);
			return curves[index].SolveCurvature(anim_clip_phase_time);
		}
	}

	/*void CompositePath::UpdateTime(float time)
	{
		for (auto p : this->curves)
		{
			if ((int)time >= p.endTime)
			{
				p.startTime += (int)time;
				p.endTime += (int)time;
			}
		}
	}*/

	std::vector<BezierCurve>& CompositePath::GetPaths()
	{
		return curves;
	}

}