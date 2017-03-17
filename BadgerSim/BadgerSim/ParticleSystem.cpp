#include <tyga/Math.hpp>
#include "ParticleSystem.hpp"
#include "MyUtils.hpp"

void MyParticleSystem::
Init(int maxParticles_, int spawnRate_)
{
	maxParticles = maxParticles_;
	spawnRate = spawnRate_;
	particles.reserve(maxParticles);
	for (int i = 0; i < maxParticles; ++i)
		particles.push_back(MyParticleSystem::Particle());
}

void MyParticleSystem::
SetColourOverLife(tyga::Vector3& startColour, tyga::Vector3& endColour)
{
	startCol = startColour;
	endCol = endColour;
	for (int i = 0; i < maxParticles; ++i)
	{
		particles[i].property.startColour = startColour;
		particles[i].property.endcolour = endColour;
	}
}

/*
Loop through all the particles that are alive in the vector. If the particles life has expired,
reset the particle and swap it with the latest active particle (cold storage). This makes it more
efficient than storing either alive and dead particles separately or by storing a flag.  If its
still alive, then update its position, lifetime, and render properties based on how long the particle
was active for.  
*/
void MyParticleSystem::
Update(float deltaTime)
{
	for (int i = 0; i < aliveParticles; ++i)
	{
		auto& particle = particles[i];

		if (particle.life > maxLifetime)
		{
			particle.position = tyga::Vector3(-500, -500, -500);
			particle.velocity = tyga::Vector3(0, 0, 0);
			particle.property.startColour = startCol;
			particle.property.endcolour = endCol;
			particle.property.currentcolour = particle.property.startColour;
			particle.life = 0;
			particle.property.alpha = 0;
			particle.property.size = 0;
			aliveParticles--;
			std::swap(particles[aliveParticles], particle);

		}
		else
		{
			particle.position += (particle.velocity * deltaTime);
			particle.life += deltaTime;
			particle.property.alpha = 1 - (particles[i].life / maxLifetime);
			particle.property.size = ((particles[i].life / maxLifetime) / 2) + 0.5f;
			particle.property.currentcolour = FB::Lerp<tyga::Vector3>(
				particle.property.startColour,
				particle.property.endcolour,
				(particles[i].life / maxLifetime));
		}
	}
}
