#pragma once
#include "Actor.h"
#include "Engine.h"
#include "Projectile.h"
#include "Player.h"
#include "World.h"

class Asteroid : public Actor
{
private:
	float Scale = 0.f;
	float RotationSpeed = 0.f;

	glm::vec3 FallDirection;
	glm::vec3 RotationAxis;

public:

	void OnHit(Actor* HitedActor);

	void Init();

	void Update(float DeltaTime);

	Asteroid();
	~Asteroid();
};



