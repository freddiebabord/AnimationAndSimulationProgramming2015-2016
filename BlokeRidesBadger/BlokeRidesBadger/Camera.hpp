#pragma once

#include <tyga/ActorDelegate.hpp>

class Badger;

class Camera : public tyga::ActorDelegate
{
public:

    Camera();

    void
    setHeadingAngle(float radians);

    void
    setHeadingSpeed(float speed);

    void
    setPanDistance(float distance);

    void
    setPanSpeed(float speed);

	void SetTargetBader(std::shared_ptr<Badger> badger){ badger_ = badger; };

	void SetShouldFollow(bool t){ shouldFollow = t; };

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<tyga::Actor> camera_actor_;
    float heading_angle_;
    float heading_speed_;
    float pan_distance_;
    float pan_speed_;
	bool shouldFollow = false;
	std::shared_ptr<Badger> badger_;
};
