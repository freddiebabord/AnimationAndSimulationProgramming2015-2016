#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/Math.hpp>

class DominantBall : public tyga::ActorDelegate
{
public:

    DominantBall();

    void
    reset(tyga::Vector3 initial_position,
          tyga::Vector3 initial_velocity);
	
	const float GetMass() { return mass; };
	
private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

	float savedTime = 0;

    tyga::Vector3 initial_position_;
    tyga::Vector3 initial_velocity_;
	
	tyga::Vector3 acceleration_;

	float mass = 5.0f;

	const tyga::Vector3 gravity = tyga::Vector3(0, 0, -9.8f);
};
