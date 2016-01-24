#pragma once
#include <tyga/Math.hpp>
#include <tyga\ActorDelegate.hpp>
#include <vector>
#include <iostream>

namespace FB{

	struct curveElemet
	{
		curveElemet(int id, float param_, double dist){ curveID = id;  param = param_; accumilatedDistance = dist; }
		int curveID = 0;
		float param = 0.0f;
		double accumilatedDistance = 0.0;
	};

	struct CombinedParam
	{
		CombinedParam(){};
		CombinedParam(int id, float param_){ curveID = id; param = param_; };
		int curveID = 0;
		float param = 0;
	};

	class BezierCurve
	{
	public:
		BezierCurve(tyga::Vector3 path[4], int curveID_)
		{
			for (int i = 0; i < 4; i++)
			{
				path_.push_back(path[i]);
			}
			curveID = curveID_;
		};
		BezierCurve(){};
		BezierCurve(int curveID_){ curveID = curveID_; };
		~BezierCurve(){};

		tyga::Vector3 Solve(float time);
		tyga::Vector3 SolveTangent(float time);
		tyga::Vector3 SolveCurvature(float time);
		tyga::Vector3 SolveForArcLength(float time);

		std::vector<tyga::Vector3>& GetPaths() { return path_; };
		void AddParam(float value_){ param.push_back(value_); };
		std::vector<float>& GetParam(){ return param; };
		
	private:
		std::vector<tyga::Vector3> path_;
		std::vector<float> param;
		int curveID = 0;
	};

	class CompositePath
	{
	public:
		CompositePath(){};
		~CompositePath(){};

		void AddCurve(BezierCurve bezierCurve);

		tyga::Matrix4x4 Animate(float time, int paramId = 0);
		tyga::Vector3 positionSolve(float time);
		tyga::Vector3 directionSolve(float time);
		tyga::Vector3 curvatureSolve(float time);
		/*void UpdateTime(float time);*/

		std::vector<BezierCurve>& GetPaths();
		void SetPathTime(float start_, float end_){ startTime = start_; endTime = end_; };
		
		std::vector<curveElemet> ArcLength(int samplePoints = 30)
		{
			float distance = 0.0;
			std::vector<FB::curveElemet> compositeCurvePoints;
			for (int i = 0; i < curves.size(); ++i)
			{
				for (int j = 0; j < samplePoints; ++j)
				{
					tyga::Vector3 a = curves[i].Solve(j);
					tyga::Vector3 b;

					if (j >= samplePoints)
						b = curves[i].Solve(j+1);
					else if (i < curves.size()-1)
						b = curves[i+1].Solve(0);
					else
						b = curves[0].Solve(0);
					
					float x = b.x - a.x;
					float y = b.y - a.y;
					float z = b.z - a.z;

					float dist = sqrt(x*x + y*y + z*z);
					distance += dist;
					std::cout << distance << std::endl;
					compositeCurvePoints.push_back(curveElemet(i, distance, distance));
				}
			}

			for (int j = 0; j < compositeCurvePoints.size(); ++j)
			{
				compositeCurvePoints[j].param /= distance;
				
			}

			return compositeCurvePoints;
		}
	private:
		std::vector<BezierCurve> curves;
		float startTime = 0;
		float endTime = 0;
	};

}