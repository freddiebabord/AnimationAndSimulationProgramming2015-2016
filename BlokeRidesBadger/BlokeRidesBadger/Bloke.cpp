#include "Bloke.h"
#include "Badger.hpp"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <pugixml/pugixml.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


#define Vec3 tyga::Vector3

Bloke::
Bloke()
{
	
}

void Bloke::
SetXFormFromBadger(tyga::Matrix4x4 newBadgerXForm)
{
	badgerXForm = newBadgerXForm;
}

void Bloke::
SwitchPose(std::string pose)
{
	if (targetPose != pose)
	{
		const float time = tyga::BasicWorldClock::CurrentTime();
		animStartTime = time;
		animStopTime = time + 0.095f;
		targetPose = pose;
	}
}

void Bloke::
SwitchPose()
{
	const float time = tyga::BasicWorldClock::CurrentTime();

	animStartTime = time;
	animStopTime = time + 0.25f;


	switch (currentPose)
	{
	case sitting_straight:
		currentPose = sitting_turn_right;
		//rootNode->ApplyTransform("sitting_turn_right");
		oldPose = "sitting_straight";
		pose = "sitting_turn_right";
		break;
	case sitting_turn_right:
		currentPose = sitting_turn_left;
		//rootNode->ApplyTransform("sitting_turn_left");
		oldPose = "sitting_turn_right";
		pose = "sitting_turn_right";
		break;
	case sitting_turn_left:
		currentPose = standing_straight;
		//rootNode->ApplyTransform("standing_straight");
		pose = "standing_straight";
		oldPose = "sitting_turn_left";
		break;
	case standing_straight:
		currentPose = standing_turn_left;
		//rootNode->ApplyTransform("standing_turn_left");
		pose = "standing_turn_left";
		oldPose = "standing_straight";
		break;
	case standing_turn_left:
		currentPose = standing_turn_right;
		//rootNode->ApplyTransform("standing_turn_right");
		pose = "standing_turn_right";
		oldPose = "standing_turn_left";
		break;
	case standing_turn_right:
		currentPose = sitting_straight;
		//rootNode->ApplyTransform("sitting_straight");
		pose = "sitting_straight";
		oldPose = "standing_turn_right";
		break;
	default:
		break;
	}
	
}


#define SPGraphics std::shared_ptr<tyga::GraphicsCentre>
#define SPWorld std::shared_ptr<tyga::ActorWorld>

void Bloke::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
	auto world = tyga::ActorWorld::defaultWorld();
	auto graphics = tyga::GraphicsCentre::defaultCentre();

	//Create the chassis material
	SPMat blokeMat = graphics->newMaterial();
	blokeMat->texture = "Bloke.tcf/colour_texture";
	blokeMat->colour = Vec3(143 / 255, 255 / 255, 143 / 255);
	

	rootNode = FB::GenerateHeriachyFromXML("bloke.xml");
	rootNode->ApplyTransform("sitting_straight", 1);
}

void Bloke::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
	auto world = tyga::ActorWorld::defaultWorld();
}


void Bloke::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
	const float time = tyga::BasicWorldClock::CurrentTime();
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();
	
	if (time > globalAnimStopTime)
	{
		globalAnimStartTime += 7;
		globalAnimStopTime += 7;
	}

	//Base transforma matrix so it'll be on the floor
	auto xform = tyga::Matrix4x4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0.725f, -0.029, 1);

	auto anim_clip_phase_time = FB::linearstep(animStartTime, animStopTime, time);
	auto globalAnim_clip_phase_time = FB::smootherStep(globalAnimStartTime, globalAnimStopTime + 1, time);

	//rootNode->SetPoseLerpTime(anim_clip_phase_time);
	rootNode->ApplyTransform(targetPose, anim_clip_phase_time);
	
	//Apply the base transform on the root node which is then passed to its children
	rootNode->ApplyTransform(xform * actor->Transformation() * badger_->GetRailXForm());
}
