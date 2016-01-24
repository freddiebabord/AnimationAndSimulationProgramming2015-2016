#pragma once

#include <tyga/ApplicationDelegate.hpp>
#include <tyga/GraphicsRendererProtocol.hpp>

class Badger;
class BadgerRails;
class Camera;
class Bloke;

class MyDemo : public tyga::ApplicationDelegate
{
public:

    MyDemo();

private:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed);

    virtual void
    applicationDidStart() override;

    virtual void
    applicationRunloopWillBegin() override;

    virtual void
    applicationRunloopDidEnd() override;

    virtual void
    applicationWillStop() override;

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state) override;

    std::shared_ptr<tyga::GraphicsRendererProtocol> renderer_;

    enum CameraMode { kCameraStatic, kCameraTracking, kCameraMAX };
    CameraMode camera_mode_;

    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Badger> badger_;
    std::shared_ptr<BadgerRails> badger_rails_;
	std::shared_ptr<Bloke> bloke_;
};
