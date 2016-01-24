#include "MyDemo.hpp"
#include <tyga/Application.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/InputStateProtocol.hpp>
#include <tyga/BasicRenderer.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <iostream>

const tyga::Vector2 MyDemo::MIN_BOUND = tyga::Vector2(-7, -3);
const tyga::Vector2 MyDemo::MAX_BOUND = tyga::Vector2(7, 3);

void MyDemo::
applicationWindowWillInit(int& width,
                          int& height,
                          int& sample_count,
                          bool& windowed)
{
    width = 1024;
    height = 576;

    std::cout << "Mystery Balls Tutorial" << std::endl;
    std::cout << "  Press spacebar to reset the balls." << std::endl;
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

    auto camera = graphics->newCamera();
    camera->vertical_field_of_view_radians = 0.8f;
    camera->xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                           0,       0,       1,       0,
                                           0,      -1,       0,       0,
                                           0,     -13,       3,       1);

    auto camera_actor = std::make_shared<tyga::Actor>();
    camera_actor->attachComponent(camera);
    world->addActor(camera_actor);

    auto floor_model = graphics->newModel();
    floor_model->material = graphics->newMaterial();
    floor_model->material->colour = tyga::Vector3(0.5f, 0.5f, 0.5f);
    floor_model->mesh = graphics->newMeshWithIdentifier("cube");

    auto floor_xform = tyga::Matrix4x4(   16,       0,       0,       0,
                                           0,      10,       0,       0,
                                           0,       0,    0.2f,       0,
                                           0,       0,   -0.1f,       1);
    auto floor_actor = std::make_shared<tyga::Actor>();
    floor_actor->attachComponent(floor_model);
    floor_actor->setTransformation(floor_xform);
    world->addActor(floor_actor);


    dominant_ball_ = std::make_shared<DominantBall>();
    dominant_ball_->addToWorld(world);
    dominant_ball_->Actor()->setPriority(1);

    const int NUM_OF_SLAVE_BALLS = 5;
    slave_balls_.resize(NUM_OF_SLAVE_BALLS);
    for (int i=0; i<NUM_OF_SLAVE_BALLS; ++i) {
        slave_balls_[i] = std::make_shared<SlaveBall>();
        slave_balls_[i]->addToWorld(world);
        slave_balls_[i]->setDominator(dominant_ball_->Actor());
    }

    resetBalls();
}

void MyDemo::
applicationRunloopWillBegin()
{
   tyga::BasicWorldClock::update();
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
    if (input_state->keyboardKeyDownCount(tyga::kInputKeySpace) == 1) {
        resetBalls();
    }
}

void MyDemo::
resetBalls()
{
    std::uniform_real_distribution<float> x_rand(MIN_BOUND.x, MAX_BOUND.x);
    std::uniform_real_distribution<float> y_rand(MIN_BOUND.y, MAX_BOUND.y);

    tyga::Vector3 position = tyga::Vector3(x_rand(rand),
                                           y_rand(rand),
                                           0.5f);
    tyga::Vector3 velocity = tyga::Vector3(-position.x,
                                           -position.y,
                                           20 - tyga::length(position));
    dominant_ball_->reset(position, velocity);

    for (auto ball : slave_balls_) {
        ball->reset(tyga::Vector3(x_rand(rand), y_rand(rand), 0.5f),
                    tyga::Vector3(x_rand(rand), y_rand(rand), 0));
    }
}
