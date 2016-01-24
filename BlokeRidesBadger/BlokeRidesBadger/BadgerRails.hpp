#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/Math.hpp>
#include "MyUtils.hpp"
#include "BezierCurve.h"
#include "Node.h"
#include "Keyframer.h"

class Badger;
class Bloke;

class BadgerRails : public tyga::ActorDelegate
{
public:

    BadgerRails();
	~BadgerRails();

    void
    setTarget(std::shared_ptr<Badger> target_badger, std::shared_ptr<Bloke> target_bloke);

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<Badger> target_badger_;
	std::shared_ptr<Bloke> target_bloke_;

	float anim_start_time = 2.f;
	float anim_stop_time = 7.f;

	tyga::Vector3* pointsCurve1;

	tyga::Vector3* pointsCurve2;;
	tyga::Vector3 previousPos;
	tyga::Vector3 currentPos;
	tyga::Matrix4x4 xform;
	FB::Keyframer< FB::CombinedParam, float> keyframer;

	FB::CompositePath cPath;
};
