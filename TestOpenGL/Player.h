#pragma once
#include "Actor.h"

class Player : public Actor
{
private:

	float PlayerVelocity = 0.2f;

	float FireRate = 0.3f;

	float Cooldown = 0.f;
	float PlayerVelocityX;

	void Movemnet();

	static bool keys[1024];

public:

	void Update(float DeltaTime) override;

	void Init() override;

	void StartFire();
	void StopFire();
	void OnHit(Actor* HitedActor);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	Player();
	~Player();
};

