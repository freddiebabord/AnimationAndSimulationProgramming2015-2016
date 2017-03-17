#include "MyPhysicsCentre.hpp"
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Log.hpp>
#include <iostream>

//namespace your_name_here
//{

PhysicsObject::PhysicsObject() : mass(0)
{
}

tyga::Vector3 PhysicsObject::
position() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._30, xform._31, xform._32);
    }
    return tyga::Vector3();
}

PhysicsPlane::PhysicsPlane()
{
}

tyga::Vector3 PhysicsPlane::
normal() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

PhysicsSphere::PhysicsSphere() : radius(1)
{
}

PhysicsBox::PhysicsBox()
{
}

tyga::Vector3 PhysicsBox::
U() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._00, xform._01, xform._02);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
V() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._10, xform._11, xform._12);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
W() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::default_centre_;

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::
defaultCentre()
{
    if (default_centre_ == nullptr) {
        default_centre_ = std::make_shared<MyPhysicsCentre>();
    }
    return default_centre_;
}

MyPhysicsCentre::
MyPhysicsCentre()
{
}

MyPhysicsCentre::
~MyPhysicsCentre()
{
}

template<typename T> static void
_prune(std::list<T>& list)
{
    for (auto it = list.begin(); it != list.end(); ) {
        if (it->expired()) {
            it = list.erase(it);
        } else {
            it++;
        }
    }
}

void MyPhysicsCentre::
pruneDeadObjects()
{
    _prune(planes_);
    _prune(spheres_);
    _prune(boxes_);
}

std::shared_ptr<PhysicsPlane> MyPhysicsCentre::
newPlane()
{
    auto new_plane = std::make_shared<PhysicsPlane>();
    planes_.push_back(new_plane);
    return new_plane;
}

std::shared_ptr<PhysicsSphere> MyPhysicsCentre::
newSphere()
{
    auto new_sphere = std::make_shared<PhysicsSphere>();
    spheres_.push_back(new_sphere);
    return new_sphere;
}

std::shared_ptr<PhysicsBox> MyPhysicsCentre::
newBox()
{
    auto new_box = std::make_shared<PhysicsBox>();
    boxes_.push_back(new_box);
    return new_box;
}

/*
	A sphere is checked to see if its within an axis aligned bounding box using the
	furtherst corner as the radius of the sphere. Calculate the speed to the badger bounding box collider and get the
	magnitude of the speed vector. Set the resulting force to be the speed vector multiplied by the size of it and add
	it to the existing velocity vector. Set the colliding spheres to enable physics again.
*/
bool BoxVsSphereCollision(std::shared_ptr<PhysicsBox> box, tyga::Vector3& previousBadgerPos, std::shared_ptr<PhysicsSphere>sphere)
{
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	auto objectPosition = sphere->position();
	auto boxPosition = box->position();

	auto normal = tyga::unit(boxPosition - objectPosition);
	auto rad = abs(tyga::dot(box->U(), normal) + tyga::dot(box->V(), normal) + tyga::dot(box->W(), normal));

	if (tyga::dot(box->position(), normal) - tyga::dot(sphere->position(), normal) < rad)
	{
		auto speed = (boxPosition - previousBadgerPos) / delta_time;
		auto mag = tyga::length(speed);
		auto force = speed * mag;
		sphere->velocity += force;
		sphere->shouldPhysx = true;

		return true;
	}

	return false;
}

/*
	A sphere is checked against a plane to determine if the sphere has intersected the plane. If it has,
	and physics should be applied (if not then it prevents gittering of objects) the object needs to be positioned
	along the normal vector out of the plane  so collision isn't detected on the next frame. A bounce response is
	then calculated which calculated the reflected vector of the collision and applies the same amount of force in
	the reflected vector with the addition of the plane coefficient being taken into account.
*/
bool SphereVsPlaneCollision(std::shared_ptr<PhysicsSphere> sphere, std::shared_ptr<PhysicsPlane> plane)
{
	const float planeCoeff = 0.6f;

	// (C-Q) dot N
	auto unitNormal = tyga::unit(plane->normal());
	auto objectPosition = sphere->position();
	auto planePosition = plane->position();
	float displacementDistance = tyga::dot((objectPosition - planePosition), unitNormal) - sphere->radius;

	if (sphere->shouldPhysx)
	{
		if (displacementDistance <= 0)
		{
			//Force object higher than planes
			auto xform = sphere->Actor()->Transformation();
			tyga::Vector3 originalPos = tyga::Vector3(xform._30, xform._31, xform._32);
			auto diff = unitNormal * (0.00001f - displacementDistance);
			tyga::Vector3 position = originalPos + diff;
			xform._30 = position.x;
			xform._31 = position.y;
			xform._32 = position.z;
			sphere->Actor()->setTransformation(xform);


			// Bounce response
			tyga::Vector3 reflectedVelocity;
			auto velocity = sphere->velocity;
			reflectedVelocity = (velocity - (2 * unitNormal * (tyga::dot(velocity, unitNormal))));
			sphere->velocity = planeCoeff * reflectedVelocity;

			//Prevent gittering on the spheres against the plane
			if (tyga::length(reflectedVelocity) < 0.88f)
				sphere->shouldPhysx = false;

			return true;
		}

	}
	return false;
}

void MyPhysicsCentre::
runloopWillBegin()
{
	//Sphere Vs Plane Collision
	/*
		Each sphere is checked against each plane to determine if the sphere has intersected the plane.
		Physics is applied as soon as collision has been detected.
	*/
	
	
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	for (auto s_iter = spheres_.begin(); s_iter != spheres_.end(); s_iter++)
	{
		// only continue if a strong reference is available
		if (s_iter->expired()) continue;
		auto physicsObj = s_iter->lock();

		for (auto p_iter = planes_.begin(); p_iter != planes_.end(); p_iter++)
		{
			// only continue if a strong reference is available
			if (p_iter->expired()) continue;
			auto plane = p_iter->lock();

			SphereVsPlaneCollision(physicsObj, plane);
			
		}
	}
	
	// Box Vs Sphere collision
	/*
		Each sphere is checked against each box if it has collided and apply physics to it.
	*/
	for (auto b_iter = boxes_.begin(); b_iter != boxes_.end(); b_iter++)
	{
		if (b_iter->expired()) continue;
			auto box = b_iter->lock();


		for (auto s_iter = spheres_.begin(); s_iter != spheres_.end(); s_iter++)
		{
			// only continue if a strong reference is available
			if (s_iter->expired()) continue;
			auto physicsObj = s_iter->lock();

			BoxVsSphereCollision(box, previousBadgerPos, physicsObj);

		}
	}

	for (auto b_iter = boxes_.begin(); b_iter != boxes_.end(); b_iter++)
	{
		if (b_iter->expired()) continue;
		auto box = b_iter->lock();

		auto boxPosition = box->position();
		previousBadgerPos = boxPosition;
	}

}



/*
	Drag equation from: https://www.grc.nasa.gov/www/k-12/airplane/drageq.html
	converted into C++. The existing accelleration is velocity that needs to be 
	applied to the object and the area is the refrance area of the object
*/
tyga::Vector3 ApplyDrag(tyga::Vector3 acceleration, float area)
{
	tyga::Vector3 vsquared(acceleration.x * acceleration.x, acceleration.y * acceleration.y, acceleration.z * acceleration.z);
	return 0.47f * area * 0.5f * 1.225f * acceleration;
}

void MyPhysicsCentre::
runloopExecuteTask()
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	/*
		Loop through the spheres to updated its velocity based on accelleration, gravity and
		any existing forces applied.
	*/
	for (auto ptr : spheres_) {
		
		// only continue if a strong reference is available
		if (ptr.expired()) continue;
		auto model = ptr.lock();

		// only continue if the model is attached to an actor
		auto actor = model->Actor();
		if (actor == nullptr) continue;

		
		// fetch the current kinetic variables
		auto position = model->position();
		auto velocity = model->velocity;

		tyga::Vector3 acceleration = tyga::Vector3(0, 0, 0);

		// Apply existing force
		auto existingAcceleration = model->force / model->mass;

		// Apply gravity constantly
		tyga::Vector3 gravity = tyga::Vector3(0, -9.8f, 0);
		acceleration = gravity + existingAcceleration;

		// Apply Drag
		float sphereArea = (float)(4 * M_PI * (powf(model->radius, 2)));
		acceleration += ApplyDrag(acceleration, sphereArea);

		position += velocity * delta_time;
		velocity += acceleration * delta_time;

		if (tyga::length(velocity) > 1)
			model->shouldPhysx = true;

		if (model->shouldPhysx)
		{

			// write back the new kinetic values (position via actor's xform)
			model->velocity = velocity;
			auto xform = actor->Transformation();
			xform._30 = position.x;
			xform._31 = position.y;
			xform._32 = position.z;
			actor->setTransformation(xform);
			// reset the force
			model->force = tyga::Vector3(0, 0, 0);
		}
		
	}
}

void MyPhysicsCentre::
runloopDidEnd()
{
    pruneDeadObjects();
}

//} // end namespace
