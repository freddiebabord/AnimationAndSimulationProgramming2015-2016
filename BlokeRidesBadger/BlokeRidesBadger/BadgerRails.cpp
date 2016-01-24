#include "BadgerRails.hpp"
#include "Badger.hpp"
#include "Bloke.h"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <iostream>



BadgerRails::
BadgerRails()
{

	pointsCurve1 = new tyga::Vector3[4]{
			tyga::Vector3(-16, 0, 0),
			tyga::Vector3(-16, 0, -8),
			tyga::Vector3(7, 0, -2.5f),
			tyga::Vector3(8, 0, 0)
	};

	pointsCurve2 = new tyga::Vector3[4]{
			tyga::Vector3(8, 0, 0),
			tyga::Vector3(12, 0, 10),
			tyga::Vector3(-16, 0, 10),
			tyga::Vector3(-16, 0, 0)
	};
	FB::BezierCurve bCurve1 = FB::BezierCurve(pointsCurve1, 0);
	FB::BezierCurve bCurve2 = FB::BezierCurve(pointsCurve2, 1);
	
	cPath.AddCurve(bCurve1);
	cPath.AddCurve(bCurve2);
	cPath.SetPathTime(2.f, 7.f);
		
	std::vector<FB::curveElemet> el = cPath.ArcLength(50);

	for (int i = 0; i < el.size(); ++i)
	{
		cPath.GetPaths()[el[i].curveID].AddParam(el[i].param);
	}
	
}

BadgerRails::~BadgerRails()
{
	delete pointsCurve1;
	delete pointsCurve2;
}

void BadgerRails::
setTarget(std::shared_ptr<Badger> target_badger, std::shared_ptr<Bloke> target_bloke)
{
    target_badger_ = target_badger;
	target_bloke_ = target_bloke;
}

void BadgerRails::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void BadgerRails::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void BadgerRails::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
	const float time = tyga::BasicWorldClock::CurrentTime();
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	auto badger_xform = tyga::Matrix4x4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	if (time > anim_stop_time)
	{
		anim_start_time += 7;
		anim_stop_time += 7;
	}

	const auto anim_clip_phase_time = FB::smoothStep(anim_start_time, anim_stop_time, time);

	previousPos = tyga::Vector3(xform.m[3][0], xform.m[3][1], xform.m[3][2]);

	xform = cPath.Animate(anim_clip_phase_time);

	currentPos = tyga::Vector3(xform.m[3][0], xform.m[3][1], xform.m[3][2]);


	auto change = tyga::length(currentPos - previousPos);

	auto angle = acos(tyga::dot(currentPos, previousPos) / (tyga::length(currentPos) * tyga::length(previousPos)));
	auto a = FB::radToDeg(angle);

	if (a > 1)
	{
		target_bloke_->SwitchPose("standing_turn_right");
	}
	else
	{
		target_bloke_->SwitchPose("sitting_straight");
	}

	target_badger_->SetRailXForm(xform);
	target_badger_->SetSpeed(change * 1000);
	target_badger_->SetRotation(a * 4);
	
}
