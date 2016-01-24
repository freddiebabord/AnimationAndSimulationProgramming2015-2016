#pragma once
#include "MyUtils.hpp"
#include <tyga/ActorDelegate.hpp>
#include "Node.h"
#include "Keyframer.h"

enum PoseNames
{
	sitting_straight,
	sitting_turn_right,
	sitting_turn_left,
	standing_straight,
	standing_turn_left,
	standing_turn_right
};


class Badger;

class Bloke : public tyga::ActorDelegate
{
public:

	Bloke();

	void SetXFormFromBadger(tyga::Matrix4x4 newBadgerXForm);
	void SwitchPose();
	void SwitchPose(std::string pose);

	void SetBadgerTarget(std::shared_ptr<Badger> badger){ badger_ = badger; };

private:

	virtual void
		actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

	virtual void
		actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

	virtual void
		actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

	std::shared_ptr<FB::Node> rootNode;
	tyga::Matrix4x4 badgerXForm;
	PoseNames currentPose = PoseNames::sitting_straight;
	std::string pose = "sitting_straight";
	std::string oldPose = "sitting_straight";
	float animStartTime = 2;
	float animStopTime = 2.5f;
	float globalAnimStartTime = 2;
	float globalAnimStopTime = 7;
	std::shared_ptr<Badger> badger_;
	std::string targetPose = "";
	//FB::Keyframer<std::string, std::string, FB::smootherStep, FB::Lerp> blokePose;
};

