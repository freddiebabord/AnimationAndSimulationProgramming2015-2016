#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/GraphicsCentre.hpp>
#include "MyPhysicsCentre.hpp"
#include "ParticleSystem.hpp"

class ToyDrone : public tyga::ActorDelegate
{
public:

    ToyDrone();

    void
    reset(tyga::Vector3 position, float mass);

    void
    applyForce(tyga::Vector3 force);

    void
    trigger();

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<PhysicsSphere> physics_model_;


	std::shared_ptr<tyga::GraphicsSprite> graphic_sprite_;

	std::shared_ptr<MyParticleSystem> particle_system_;
	
};
