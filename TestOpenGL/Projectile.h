#pragma once
#include "Actor.h"
class Projectile : public Actor
{
private:
	glm::vec3 FireDirection;
public:

	void Init() override;
	void Update(float DeltaTime) override;
	void Die();
	void OnHit(Actor* HitedActor);
	Projectile();
	~Projectile();
};

