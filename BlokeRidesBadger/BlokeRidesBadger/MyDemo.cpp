#include "MyDemo.hpp"
#include "Badger.hpp"
#include "BadgerRails.hpp"
#include "Camera.hpp"
#include "Bloke.h"
#include <tyga/Application.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/InputStateProtocol.hpp>
#include <tyga/BasicRenderer.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <iostream>

MyDemo::
MyDemo()
{
    camera_mode_ = kCameraTracking;
}

void MyDemo::
applicationWindowWillInit(int& width,
                          int& height,
                          int& sample_count,
                          bool& windowed)
{
    width = 1024;
    height = 576;

    std::cout << "Animation and Simulation Programming 2015" << std::endl;
    std::cout << "Bloke Rides Badger" << std::endl << std::endl;
    std::cout << "Hold the right shoulder button to control the camera." << std::endl;
    std::cout << "Press F2 to swap camera modes." << std::endl << std::endl;
}

void MyDemo::
applicationDidStart()
{
    renderer_ = std::make_shared<tyga::BasicRenderer>();
    tyga::Application::setWindowViewDelegate(renderer_);

    tyga::Application::addRunloopTask(tyga::GraphicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::ActorWorld::defaultWorld());

    tyga::Application::setRunloopFrequency(60);


    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();


    auto floor_mesh = graphics->newMeshWithIdentifier("cube");
    auto floor_material = graphics->newMaterial();
	floor_material->colour = tyga::Vector3(1.0f, 0.47058823529f, 0.47058823529f);

    auto floor_model = graphics->newModel();
    floor_model->material = floor_material;
    floor_model->mesh = floor_mesh;
    auto floor_actor = std::make_shared<tyga::Actor>();
    floor_actor->attachComponent(floor_model);
    auto floor_xform = tyga::Matrix4x4(      80,       0,       0,       0,
                                              0,    0.2f,       0,       0,
                                              0,       0,      60,       0,
                                              0,   -0.1f,       0,       1);
    floor_actor->setTransformation(floor_xform);
    world->addActor(floor_actor);
	
    floor_material = graphics->newMaterial();
	floor_material->colour = tyga::Vector3(0.74117647058f, 0.92549019607f, 0.71372549019f);
    for (int i=0; i<4; ++i) {
        floor_model = graphics->newModel();
        floor_model->material = floor_material;
        floor_model->mesh = floor_mesh;
        floor_actor = std::make_shared<tyga::Actor>();
        floor_actor->attachComponent(floor_model);
        float x = -12.f + 8 * i;
        floor_xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                             0,       1,       0,       0,
                                             0,       0,       1,       0,
                                             x,    0.5f,       0,       1);
        floor_actor->setTransformation(floor_xform);
        world->addActor(floor_actor);
    }


    camera_ = std::make_shared<Camera>();
    camera_->addToWorld(world);


    

	bloke_ = std::make_shared<Bloke>();
	bloke_->addToWorld(world);
	bloke_->Actor()->setPriority(2);

    badger_ = std::make_shared<Badger>();
	badger_->setTarget(bloke_);
    badger_->addToWorld(world);
    badger_->Actor()->setPriority(1);

	badger_rails_ = std::make_shared<BadgerRails>();
    badger_rails_->setTarget(badger_, bloke_);
    badger_rails_->addToWorld(world);
    badger_rails_->Actor()->setPriority(3);

	bloke_->SetBadgerTarget(badger_);
	camera_->SetTargetBader(badger_);
}

void MyDemo::
applicationRunloopWillBegin()
{
    tyga::BasicWorldClock::update();

    auto camera_xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                               0,       1,       0,       0,
                                               0,       0,       1,       0,
                                               0,       1,       0,       1);
    switch (camera_mode_)
    {
    case MyDemo::kCameraStatic:
        camera_->Actor()->setTransformation(camera_xform);
        break;
    case MyDemo::kCameraTracking:
        camera_->Actor()->setTransformation(
            camera_xform * badger_->Actor()->Transformation());
        break;
    }
}

void MyDemo::
applicationRunloopDidEnd()
{
    renderer_->setGraphicsScene(tyga::GraphicsCentre::defaultCentre()->scene());
}

void MyDemo::
applicationWillStop()
{
}

void MyDemo::
applicationInputStateChanged(
    std::shared_ptr<tyga::InputStateProtocol> input_state)
{
    if (input_state->gamepadPresent(0))
    {
        if (input_state->gamepadButtonDownCount(
            0, tyga::kInputGamepadButtonRightShoulder) > 0)
        {
            float camera_heading_speed = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisRightThumbX);
            camera_->setHeadingSpeed(camera_heading_speed);
            float camera_pan_speed = -input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisLeftThumbY);
            camera_->setPanSpeed(camera_pan_speed);
        }
		if (input_state->gamepadButtonDownCount(0, 0) == 1)
			bloke_->SwitchPose();
    }
	if (input_state->keyboardKeyDownCount(tyga::kInputKeyF1) == 1) {
		bloke_->SwitchPose();
	}
    if (input_state->keyboardKeyDownCount(tyga::kInputKeyF2) == 1) {
        camera_mode_ = CameraMode((camera_mode_+1) % kCameraMAX);
        switch (camera_mode_)
        {
        case MyDemo::kCameraStatic:
            camera_->setHeadingAngle(0.2f);
            camera_->setPanDistance(30);
			camera_->SetShouldFollow(false);
            break;
        case MyDemo::kCameraTracking:
            camera_->setHeadingAngle(2);
            camera_->setPanDistance(5);
			camera_->SetShouldFollow(true);
			break;
        }
    }
}
