#pragma once
#include "MyUtils.hpp"
#include <tyga/ActorDelegate.hpp>
#include "Node.h"

class Bloke;

class Badger : public tyga::ActorDelegate
{
public:

    Badger();

	void SetRailXForm(tyga::Matrix4x4 newRailXForm);
	void setTarget(std::shared_ptr<Bloke> targetBloke);
	void SetRotation(float rotation);
	void SetSpeed(float speed);
	const tyga::Matrix4x4 GetRailXForm() { return railXForm; };
private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;


	std::shared_ptr<FB::Node> rootNode;
	std::shared_ptr<FB::Node>* wheelMoveActors;
	std::shared_ptr<FB::Node> handlebarMoveActor;

	float speed_ = 20;
	float rotation_ = 0;
	float currentSpinAngle = 0;
	

	tyga::Matrix4x4 railXForm;

	std::shared_ptr<Bloke> target_bloke_;
};
