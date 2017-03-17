#pragma once

#include <tyga/Math.hpp>
#include <tyga/ActorDelegate.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <vector>

#include <pugixml/pugixml.hpp>
#include <unordered_map>

//#include "tyroneAnim.hpp"
//#include "tyroneXform.hpp"

#include "C:\Users\Tyrone\Dropbox\code\tyroneAnim.hpp"
#include "C:\Users\Tyrone\Dropbox\code\tyroneXform.hpp"

//#include "C:\Users\u0018196\Dropbox\code\tyroneAnim.hpp"
//#include "C:\Users\u0018196\Dropbox\code\tyroneXform.hpp"


class Bloke : public tyga::ActorDelegate
{
public:

    Bloke();

    void
    setPoseWeights(float left_right, float stand_sit);


public: // TODO: this should be private

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;


private:

    // method 1
    std::vector<std::shared_ptr<tyga::Actor>> actors_;



    // method 2
    //std::shared_ptr<ActorNode> root_node_;
    std::shared_ptr<tyrone::ActorNode> animated_node_;

    std::shared_ptr<tyrone::ActorNode> pelvis_node_;
    std::shared_ptr<tyrone::ActorNode> torso_node_;
    std::shared_ptr<tyrone::ActorNode> helmet_node_;
    std::shared_ptr<tyrone::ActorNode> arm_left_node_;
    std::shared_ptr<tyrone::ActorNode> forearm_left_node_;
    std::shared_ptr<tyrone::ActorNode> hand_left_node_;
    std::shared_ptr<tyrone::ActorNode> arm_right_node_;
    std::shared_ptr<tyrone::ActorNode> forearm_right_node_;
    std::shared_ptr<tyrone::ActorNode> hand_right_node_;
    std::shared_ptr<tyrone::ActorNode> leg_left_node_;
    std::shared_ptr<tyrone::ActorNode> shin_left_node_;
    std::shared_ptr<tyrone::ActorNode> foot_left_node_;
    std::shared_ptr<tyrone::ActorNode> leg_right_node_;
    std::shared_ptr<tyrone::ActorNode> shin_right_node_;
    std::shared_ptr<tyrone::ActorNode> foot_right_node_;


    pugi::xml_document doc_;
    std::unordered_map<std::string, std::shared_ptr<tyrone::ActorNode>> nodes_;


    struct ActorPose
    {
        tyga::Vector3 translate;
        tyga::Vector3 euler;
    };

    struct EntityPose
    {
        std::unordered_map<std::string, ActorPose> actor_poses;
    };

    struct StancePose
    {
        EntityPose left_pose;
        EntityPose straight_pose;
        EntityPose right_pose;
    };

    void
    loadPose(std::string pose, EntityPose& dst);
    
    float pose_weight_left_right_;
    float pose_weight_stand_sit_;

    EntityPose default_pose_;
    StancePose standing_pose_;
    StancePose sitting_pose_;
};
