#pragma once

#include <memory>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <map>
#include <pugixml/pugixml.hpp>

namespace FB
{
	struct Transform
	{
		Transform(tyga::Vector3 pos, tyga::Vector3 rot) :
			position(pos), rotation(rot){};
		tyga::Vector3 position, rotation = tyga::Vector3(0, 0, 0);
	};

	// Node class
	class Node
	{
	public:
		//default empty constructor
		Node(){};
		//Constructer which sets the actor
		Node(std::shared_ptr<tyga::Actor> actor){ actor_ = actor; };
		~Node(){};

		//Apply transformation for the children without altering the current local transform
		void ApplyTransform() const;
		//Apply the transformation of the parent to this node
		void ApplyTransform(tyga::Matrix4x4 parentxform);
		void ApplyTransform(std::string transformName, float time);
		void ApplyTransform(std::string oldTransform, std::string transformName, float time);
		void ApplyTransform(std::string transformName, std::string tagName, tyga::Matrix4x4 localMat);
		//Set the transoformation of the node
		void setTransformation(tyga::Matrix4x4 local_xform);
		void setTransformation(std::string transformationName);
		void setTransformation(std::string tagName, tyga::Matrix4x4 xform);

		//Add a new child node
		void addChild(std::shared_ptr<Node> child);

		void AddTransform(std::string name, Transform transform);

		Transform GetTransform(std::string name);

		tyga::Matrix4x4 getXForm();
		std::vector<std::shared_ptr<Node>> nodes;
		const std::string GetName() { return nodeName; };
		void SetName(std::string name){ nodeName = name; };
		void SetTargetPose(std::string pose_){ targetPose = pose_; for (auto c : children)	c->SetTargetPose(pose_); };
		void SetPoseLerpTime(float t){ poseLerpTime = t; for (auto c : children)	c->SetPoseLerpTime(t); };
	private:
		//A vector of children
		std::vector<std::shared_ptr<Node>> children;
		//Default transform matrix for any node
		tyga::Matrix4x4 localxform_ = tyga::Matrix4x4(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		std::map<std::string, Transform> transforms;
		//Default actor set to nullptr
		std::shared_ptr<tyga::Actor> actor_ = nullptr;
		std::string nodeName = "";
		std::string currentPose = "";
		std::string targetPose = "";
		float poseLerpTime = 0.0f;
	};

	std::shared_ptr<FB::Node> CreateNode(pugi::xml_node parentXMLnode, std::string rootName);
	std::shared_ptr<FB::Node> GenerateHeriachyFromXML(char* xmlDoc);

#define SPMat std::shared_ptr<tyga::GraphicsMaterial>
#define SPNode std::shared_ptr<FB::Node>
#define SPActor std::shared_ptr<tyga::Actor>

	SPNode createHeirachyElement(SPNode parentNode, SPActor nodeActor, Transform transform = Transform(tyga::Vector3(0, 0, 0), tyga::Vector3(0, 0, 0)));

	// Create and return a new actor :: could be refactored into create node
	std::shared_ptr<tyga::Actor> CreateActor(std::string meshName,
		std::shared_ptr<tyga::GraphicsMaterial> material,
		std::shared_ptr<tyga::GraphicsCentre> graphics,
		std::shared_ptr<tyga::ActorWorld> world);

}