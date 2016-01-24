#include "Badger.hpp"
#include "Bloke.h"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>

#define Vec3 tyga::Vector3

Badger::
Badger()
{
	speed_ = 0.f;
	rotation_ = 0.f;

	for (int i = 0; i < 4; i++)
	{
		//wheelMoveActors
		wheelMoveActors = new std::shared_ptr<FB::Node>[4];
	}
}

void Badger::
setTarget(std::shared_ptr<Bloke> targetBloke)
{
	target_bloke_ = targetBloke;
}
void Badger::SetRotation(float rotation)
{
	rotation_ = rotation;
}

void Badger::SetSpeed(float speed)
{
	speed_ = speed;
}

void Badger::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();

	rootNode = FB::GenerateHeriachyFromXML("badger.xml");
	rootNode->ApplyTransform("idle", 1);

}

void Badger::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
}

void Badger::
SetRailXForm(tyga::Matrix4x4 newRailXForm)
{
	railXForm = newRailXForm;
}

void Badger::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
	const float time = tyga::BasicWorldClock::CurrentTime();
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	//Base transforma matrix so it'll be on the floor
	auto xform = tyga::Matrix4x4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0.756, -0.075, 1);

	//// Slow down speed until speed is 0
	//if (speed_ > 0)
	//	speed_ -= 5;
	//if (speed_ < 0)
	//	speed_ += 5;

	//
	//Prevents jumping and then slowing down
	currentSpinAngle += FB::Continuous(0.f, speed_, delta_time);
	
	//The movement matricies for each wheel
	tyga::Matrix4x4 wheelMatricies[4] = {
		FB::rotateY(currentSpinAngle) * FB::rotateX(rotation_), // Left front wheel
		FB::rotateY(-currentSpinAngle) * FB::rotateX(-rotation_), // Right front wheel
		FB::rotateY(currentSpinAngle), // Left back wheel
		FB::rotateY(-currentSpinAngle)  // Right back wheel
	};

	////Set the wheel matricies for each wheel movement node
	rootNode->ApplyTransform("idle", "handlebar", FB::rotateY(rotation_ * -1));

	//for (int i = 0; i < 4; i++)
	//{
//	wheelMoveActors[i]->setTransformation(wheelMatricies[i]);
	//}

	//currentSpinAngle += FB::Continuous(1.f, 5000.f, delta_time);

	rootNode->ApplyTransform("idle", "leftBackWheel", wheelMatricies[2]);
	rootNode->ApplyTransform("idle", "rightBackWheel", wheelMatricies[3]);
	rootNode->ApplyTransform("idle", "rightFrontWheel", wheelMatricies[1]);
	rootNode->ApplyTransform("idle", "leftFrontWheel", wheelMatricies[0]);

	target_bloke_->SetXFormFromBadger(xform * railXForm);
	//Apply the base transform on the root node which is then passed to its children
	rootNode->ApplyTransform(xform * railXForm);
}
