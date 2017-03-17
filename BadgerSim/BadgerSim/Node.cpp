#include "MyUtils.hpp"
#include "Node.h"
#include <string>
#include <sstream>
namespace FB{

	void Node::ApplyTransform(tyga::Matrix4x4 parentxform)
	{
		auto worldxform = localxform_ * parentxform;
		//If the the node has an actor then set its transform
		if (actor_)
		{
			actor_->setTransformation(worldxform);
		}
		//Apply the world transform to the nodes children
		for each (auto c in children)
		{
			c->ApplyTransform(worldxform);
		}
	};

	void Node::ApplyTransform(std::string transformName, std::string tagName, tyga::Matrix4x4 localMat)
	{
		if (transforms.find(transformName) != transforms.end() && nodeName == tagName)
			localxform_ = localMat * rotate(GetTransform(transformName).rotation) * translate(GetTransform(transformName).position.x, GetTransform(transformName).position.y, GetTransform(transformName).position.z);
		//else if (transforms.find(transformName) != transforms.end() && nodeName != tagName)
		//	localxform_ = rotate(GetTransform(transformName).rotation) * translate(GetTransform(transformName).position.x, GetTransform(transformName).position.y, GetTransform(transformName).position.z);
		//else if (nodeName == tagName)
		//	localxform_ = localMat;
		for each (auto c in children)
		{
			c->ApplyTransform(transformName, tagName, localMat);
		}
	};

	void Node::ApplyTransform(std::string transformName, float time)
	{
		targetPose = transformName;

		if (currentPose == "")
			localxform_ = rotate(GetTransform(targetPose).rotation) * translate(GetTransform(targetPose).position);
		else if (transforms.find(targetPose) != transforms.end())
		{
			tyga::Vector3 rotation = GetTransform(targetPose).rotation;
			tyga::Vector3 rotationOld = GetTransform(currentPose).rotation;
			tyga::Vector3 translation = GetTransform(targetPose).position;
			tyga::Vector3 translationOld = GetTransform(currentPose).position;
			localxform_ =/* QuaternionToMatrix(SLerp(rotationOld, rotation, 1)) * */ rotate(Lerp(rotationOld, rotation, time)) * translate(Lerp(translationOld, translation, time));
		}
		for each (auto c in children)
		{
			c->ApplyTransform(transformName, time);
		}

		if (time >= 0.95f)
			currentPose = targetPose;
	};

	void Node::ApplyTransform() const
	{
		//If the the node has an actor then set its transform
		if (actor_ != nullptr)
		{
			actor_->setTransformation(localxform_);
		}
		//Apply the world transform to the nodes children
		for each (auto c in children)
		{
			c->ApplyTransform(localxform_);
		}
	};

	void Node::ApplyTransform(std::string oldTransform, std::string transformName, float time)
	{
		tyga::Vector3 rotation = GetTransform(transformName).rotation;
		tyga::Vector3 rotationOld = GetTransform(oldTransform).rotation;
		tyga::Vector3 translation = GetTransform(transformName).position;
		tyga::Vector3 translationOld = GetTransform(oldTransform).position;

		localxform_ =/* QuaternionToMatrix(SLerp(rotationOld, rotation, 1)) * */ rotate(Lerp(rotationOld, rotation, time)) * translate(Lerp(translationOld, translation, time));

		for each (auto c in children)
		{
			c->ApplyTransform(oldTransform, transformName, time);
		}
	};

	void Node::setTransformation(tyga::Matrix4x4 local_xform)
	{
		//Set the nodes transform matrix to the new local transform matrix
		localxform_ = local_xform;
	};

	void Node::setTransformation(std::string transformationName)
	{
		localxform_ = rotate(GetTransform(transformationName).rotation) * translate(GetTransform(transformationName).position.x, GetTransform(transformationName).position.y, GetTransform(transformationName).position.z);
		
	};

	void Node::setTransformation(std::string tagName, tyga::Matrix4x4 xform)
	{
		//If the the node has an actor then set its transform
		if (nodeName == tagName)
		{
			localxform_ = xform;
		}
		//Apply the world transform to the nodes children
		for each (auto c in children)
		{
			c->setTransformation(tagName, xform);
		}
	};

	void Node::addChild(std::shared_ptr<Node> child)
	{
		//Add a new child node to the list
		children.push_back(child);
	};

	void Node::AddTransform(std::string name, Transform transform)
	{
		transforms.insert(std::pair<std::string, Transform>(name, transform));
	}

	Transform Node::GetTransform(std::string name)
	{
		return transforms.find(name)->second;
	}

	tyga::Matrix4x4 Node::getXForm()
	{
		return localxform_;
	}

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	std::shared_ptr<FB::Node> CreateNode(pugi::xml_node parentXMLnode, std::string rootName)
	{
		auto world = tyga::ActorWorld::defaultWorld();
		auto graphics = tyga::GraphicsCentre::defaultCentre();
		
		pugi::xml_node xmlNode = parentXMLnode;// .child("actor");
		std::string meshName = xmlNode.attribute("name").as_string();
		std::shared_ptr<FB::Node> node;
		std::string tag = xmlNode.attribute("tag").as_string();
		
		if (meshName != "")
		{
			std::vector<std::string> col;
			split(xmlNode.attribute("colour").as_string(), ' ', col);

			auto material = graphics->newMaterial();
			material->texture = rootName + ".tcf/colour_texture";
			material->colour = tyga::Vector3(std::atof(col[0].c_str()) / 255, std::atof(col[1].c_str()) / 255, std::atof(col[2].c_str()) / 255);
			//Create the base
			std::shared_ptr<tyga::Actor> actor = FB::CreateActor(rootName + ".tcf/" + meshName, material, graphics, world);

			node = std::make_shared<FB::Node>(actor);

			for (pugi::xml_node poseNode = xmlNode.child("poses").child("pose"); poseNode; poseNode = poseNode.next_sibling("pose"))
			{
				std::vector<std::string> pos, rot;

				split(poseNode.attribute("translate").as_string(), ' ', pos);
				split(poseNode.attribute("euler").as_string(), ' ', rot);

				Transform trans = Transform(tyga::Vector3(std::atof(pos[0].c_str()), std::atof(pos[1].c_str()), std::atof(pos[2].c_str())),
					tyga::Vector3(std::atof(rot[0].c_str()), std::atof(rot[1].c_str()), std::atof(rot[2].c_str())));
				node->AddTransform(poseNode.attribute("name").as_string(), trans);
			}
		}
		else
			node = std::make_shared<FB::Node>();
		if (tag != "")
			node->SetName(tag);

		for (auto c : xmlNode.children("actor"))
		{
			node->addChild(CreateNode(c, rootName));
		}

		return node;
	}

	std::shared_ptr<FB::Node> GenerateHeriachyFromXML(char* xmlDoc)
	{

		pugi::xml_document doc;

		pugi::xml_parse_result result = doc.load_file(xmlDoc);
		if (result)
		{
			std::string entityName = doc.child("entity").attribute("name").as_string();
			return FB::CreateNode(doc.child("entity").child("actor"), entityName);

		}
	}

	SPNode createHeirachyElement(SPNode parentNode, SPActor nodeActor, Transform transform)
	{
		std::shared_ptr<FB::Node> staticNode = std::make_shared<FB::Node>(nodeActor);
		//Apply the static transformation to the actor
		staticNode->setTransformation(FB::rotate(transform.rotation.x, transform.rotation.y, transform.rotation.z) * FB::translate(transform.position.x, transform.position.y, transform.position.z));
		//Add the movement node for the luggage rack to the root nodes children.
		parentNode->addChild(staticNode);
		return staticNode;
	}


	std::shared_ptr<tyga::Actor> CreateActor(std::string meshName,
		std::shared_ptr<tyga::GraphicsMaterial> material,
		std::shared_ptr<tyga::GraphicsCentre> graphics,
		std::shared_ptr<tyga::ActorWorld> world)
	{
		//Create an empty actor, new matrial and mesh
		auto child_actor = std::make_shared<tyga::Actor>();
		auto child_material = graphics->newMaterial();
		std::shared_ptr<tyga::GraphicsMesh>  child_mesh;

		//Assign the material and mesh values
		child_material = material;
		child_mesh = graphics->newMeshWithIdentifier(meshName);

		//Create the model
		auto child_model = graphics->newModel();

		//Apply the mesh and material to the model
		child_model->material = child_material;
		child_model->mesh = child_mesh;
		child_actor->attachComponent(child_model);

		//Add the new actor to the world
		world->addActor(child_actor);

		//Create a delete so the component can animate
		auto child_delegate = std::make_shared<tyga::ActorDelegate>();
		child_actor->setDelegate(child_delegate);

		//Return a reference to the new actor
		return child_actor;
	}
}