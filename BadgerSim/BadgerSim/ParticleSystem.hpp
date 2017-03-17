#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/GraphicsCentre.hpp>

class MyParticleSystem : public tyga::GraphicsSpriteDelegate,
	public std::enable_shared_from_this<MyParticleSystem>
{
public:

	struct Particle {
		tyga::Vector3 position = tyga::Vector3(0, -5.0f, 0);
		tyga::Vector3 velocity = tyga::Vector3(0, 0, 0);
		float life = 0.0f;

		struct Properties
		{
			tyga::Vector3 startColour;
			tyga::Vector3 endcolour;
			tyga::Vector3 currentcolour;
			float alpha = 0;
			float size = 1;
		} property;
	};

	// Container of particles
	std::vector<Particle> particles;

	void Init(int maxParticles, int spawnRate_);
	void SetColourOverLife(tyga::Vector3& startColour, tyga::Vector3& endColour);

	std::string
		graphicsSpriteTexture() const override;

	int
		graphicsSpriteVertexCount() const override;

	void
		graphicsSpriteGenerate(
		tyga::GraphicsSpriteVertex vertex_array[]) const override;

	void
		Update(float deltaTime);

	int aliveParticles = 0;
	float maxLifetime = 1.0f;
	float particlesToBirth = 0.0f;
	int spawnRate = 20;
	int maxParticles;
	tyga::Vector3 startCol = tyga::Vector3(1, 1, 1), endCol = tyga::Vector3(1, 1, 1);
};
