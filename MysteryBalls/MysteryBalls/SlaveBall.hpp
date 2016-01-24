#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/Math.hpp>

class SlaveBall : public tyga::ActorDelegate
{
public:

    SlaveBall();

    void
    reset(tyga::Vector3 position,
          tyga::Vector3 velocity);

    void
    setDominator(std::shared_ptr<tyga::Actor>);

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<tyga::Actor> dominator_;

	
	float mass = 0.5f;
	float savedTime = 0;
    tyga::Vector3 position_;
    tyga::Vector3 velocity_;

	const tyga::Vector3 gravity = tyga::Vector3(0, 0, -9.8f);
};
