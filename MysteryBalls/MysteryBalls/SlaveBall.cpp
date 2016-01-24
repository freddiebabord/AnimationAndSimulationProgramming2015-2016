#include "SlaveBall.hpp"
#include "MyUtils.hpp"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>

SlaveBall::
SlaveBall()
{
}

void SlaveBall::
reset(tyga::Vector3 position,
      tyga::Vector3 velocity)
{
    position_ = position;
    velocity_ = velocity;
	const float time = tyga::BasicWorldClock::CurrentTime();
	savedTime = time;
}

void SlaveBall::
setDominator(std::shared_ptr<tyga::Actor> dominator)
{
    dominator_ = dominator;
}

void SlaveBall::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
    model->material->colour = tyga::Vector3(0.25f, 1.f, 0.15f);
    model->mesh = graphics->newMeshWithIdentifier("sphere");

    actor->attachComponent(model);
}

void SlaveBall::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

float Distance(tyga::Vector3 c1, tyga::Vector3 c2)
{
	//(Dx*Dx+Dy*Dy+Dz*Dz)^.5 
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)(dx * dx + dy * dy + dz * dz));
}

void SlaveBall::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    // TODO: implement numerical integration to update position_

    const tyga::Vector3& P = position_;
    auto xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                        0,       1,       0,       0,
                                        0,       0,       1,       0,
                                      P.x,     P.y,     P.z,       1);

	tyga::Vector3 domPos = tyga::Vector3(dominator_->Transformation().m[3][0], dominator_->Transformation().m[3][3], dominator_->Transformation().m[3][2]);

	auto t = tyga::Vector3(actor->Transformation().m[3][0], actor->Transformation().m[3][3], actor->Transformation().m[3][2]);

	float mass = rand() % 5 - 0;

	auto a = (mass * 5.0f) / pow(Distance(domPos, t), 2);

	auto F = mass * t;
/*
	tyga::Vector3 displacement = velocity_ * (time - savedTime)+0.5f * acceleration_ * pow(time - savedTime, 2);
	tyga::Vector3 displacement = initial_velocity_ * (time - savedTime) + 0.5f * acceleration_ * pow(time - savedTime, 2);*/

	actor->setTransformation(xform * a);
}
