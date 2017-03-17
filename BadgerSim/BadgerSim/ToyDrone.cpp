#include "ToyDrone.hpp"
#include "MyUtils.hpp"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/Log.hpp>
#include <cassert>
#include <random>

/*
Caluclate a random unit vector based on normal distribution.
*/
tyga::Vector3 RandomUnitVector()
{
	std::default_random_engine rand;
	std::normal_distribution <float> dist(0, 1);
	std::normal_distribution <float> dist2(-1, 1);
	auto u = dist(rand);
	auto v = dist2(rand);
	auto theta = acos(v);
	auto delta = 2 * M_PI * u;

	return tyga::Vector3((float)(sin(theta) * cos(delta)), (float)(sin(theta) * cos(delta)), (float)cos(theta));
}

ToyDrone::
ToyDrone()
{
}

void ToyDrone::
reset(tyga::Vector3 position, float mass)
{
    // NB: this method should not need changing

    const auto& p = position;
    auto xform = tyga::Matrix4x4(    1,   0,   0,  0,
                                     0,   1,   0,  0,
                                     0,   0,   1,  0,
                                   p.x, p.y, p.z,  1);
    Actor()->setTransformation(xform);
    physics_model_->mass = mass;
}

void ToyDrone::
applyForce(tyga::Vector3 force)
{
    // NB: this method should not need changing

    physics_model_->force += force;
}

void ToyDrone::
trigger()
{
    // NB: this method should not be changed

    assert(false && "ToyDrone::trigger method should not be used");
    tyga::debugLog("ToyDrone::trigger: toy should explode now");
}

void ToyDrone::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();
    auto physics = MyPhysicsCentre::defaultCentre();

    auto graphics_model = graphics->newModel();
    graphics_model->material = graphics->newMaterial();
    graphics_model->material->colour = tyga::Vector3(1, 0.33f, 0);
    graphics_model->mesh = graphics->newMeshWithIdentifier("sphere");
    graphics_model->xform = tyga::Matrix4x4( 0.5f,    0,    0,   0,
                                                0, 0.5f,    0,   0,
                                                0,    0, 0.5f,   0,
                                                0,    0,    0,   1);

    auto physics_model = physics->newSphere();
    physics_model->radius = 0.25f;
    physics_model->mass = 1.f;
    physics_model_ = physics_model;

    actor->attachComponent(graphics_model);
    actor->attachComponent(physics_model);
    world->addActor(actor);

	/*
		Initialise the particle system with a maximum of 200 particles.
		Set the sprite of the system to one created int he graphics system.
	*/
	particle_system_ = std::make_shared<MyParticleSystem>();
	particle_system_->Init(300, 30);
	particle_system_->SetColourOverLife(tyga::Vector3(0.1f, 0.1f, 0.1f), tyga::Vector3(1, 1, 1));
	graphic_sprite_ = graphics->newSpriteWithDelegate(particle_system_);
}

void ToyDrone::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}



/*
	Spawn the amount of particles that are supposed to be spawned this frame and keep take of any 
	leftovers for the following frame to spawn. Set the particles position to be in the same position
	as the toy drone. Update the particle system with the time since the last frame (delta time).
*/
void ToyDrone::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
	const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

	// Obtain position and direction from emitter
	tyga::Matrix4x4 source_xform = actor->Transformation();
	tyga::Vector3 source_position(source_xform._30, source_xform._31, source_xform._32);
	tyga::Vector3 source_direction = -(physics_model_->velocity);
	
	if (tyga::length(physics_model_->velocity) > 0.88f)
	{
		particle_system_->particlesToBirth += particle_system_->spawnRate * delta_time;

		int spawnedParticles = 0;
		for (spawnedParticles = 0; spawnedParticles < particle_system_->particlesToBirth; ++spawnedParticles)
		{
			if (particle_system_->aliveParticles + spawnedParticles < particle_system_->maxParticles)
			{
				auto& particle = particle_system_->particles[particle_system_->aliveParticles + spawnedParticles];
				particle.position = source_position;
				particle.velocity = RandomUnitVector();
				particle.life = 0.0f;
				particle_system_->aliveParticles++;
			}
		}
		particle_system_->particlesToBirth -= spawnedParticles;
	}
	particle_system_->Update(delta_time);
}

std::string MyParticleSystem::
graphicsSpriteTexture() const
{
	return "particle.png";
}

int MyParticleSystem::
graphicsSpriteVertexCount() const
{
	// NB: you may need to adjust this count if you keep dead particles
	return aliveParticles;
}

void MyParticleSystem::
graphicsSpriteGenerate(tyga::GraphicsSpriteVertex vertex_array[]) const
{
	// NB: you may need to adjust this if you want to control the sprite look
	for (unsigned int i = 0; i < (unsigned int)graphicsSpriteVertexCount() ; ++i) {
		vertex_array[i].position = particles[i].position;
		vertex_array[i].size = particles[i].property.size;
		vertex_array[i].colour = particles[i].property.currentcolour;
		vertex_array[i].alpha = particles[i].property.alpha;
		vertex_array[i].rotation = 0.f; // NB: has no effect in basic renderer
	}
}
