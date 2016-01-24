#include "DominantBall.hpp"
#include "MyUtils.hpp"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <iostream>


DominantBall::
DominantBall()
{
}


void DominantBall::
reset(tyga::Vector3 initial_position,
      tyga::Vector3 initial_velocity)
{
    initial_position_ = initial_position;
    initial_velocity_ = initial_velocity;
	const float time = tyga::BasicWorldClock::CurrentTime();
	savedTime = time;
	acceleration_ = gravity;

	//endTime = (gravity - initial_velocity) / acceleration_;

}

void DominantBall::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto model = graphics->newModel();
    model->material = graphics->newMaterial();
    model->material->colour = tyga::Vector3(1.f, 0.15f, 0.15f);
    model->mesh = graphics->newMeshWithIdentifier("sphere");

    actor->attachComponent(model);
}

void DominantBall::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}


void DominantBall::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();


    // TODO: implement projectile motion to compute position
    tyga::Vector3 position;

	

    const tyga::Vector3& P = position;
    auto xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                        0,       1,       0,       0,
                                        0,       0,       1,       0,
                                      P.x,     P.y,     P.z,       1);


	tyga::Vector3 displacement = initial_velocity_ * (time - savedTime) + 0.5f * acceleration_ * pow(time - savedTime, 2);



    actor->setTransformation(xform * FB::translate(displacement));
}
