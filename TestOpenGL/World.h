#pragma once
#include "Math.h"
#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"

class Player;

class World
{
private:

	static World* Instance;

	Player* LocalPlayer = nullptr;

	std::vector<Actor*> ActiveActor;

	std::vector<Actor*> DeadActor;

	static const int PoolSize = 1000;
	
	float MaxInterval = 0.f;
	float MinInterval = 0.f;
	float CurrentInterval = 0.f;
	float DeltaInterval = 0.f;

	static bool RemoveActor(Actor* CheckActor);
	bool CheckActorIsAliave(Actor* CheckActor);
	
public:

	void SpawnAsteroid();

	static World* GetInstance();

	void Init();

	void Update(float DeltaTime);

	void OnRestart();

	void ChangeSpawnTime();

	void RestartGame();

	Player* GetLocalPlayer();
	const std::vector<Actor*> GetActorsItr();

	template<typename TargetT>
	TargetT* SpawnActor(glm::vec3 NewPos, Actor* Owner)
	{
		Actor* NewActor = nullptr;
		if (NewActor == nullptr)
		{
			if (!this->DeadActor.empty())
			{
				NewActor = this->DeadActor.back();
				this->DeadActor.pop_back();
				if (NewActor != nullptr)
				{
					Actor* tmpActor(new TargetT);
					NewActor = tmpActor;
				}
			}
			NewActor->SetOwner(Owner);
			NewActor->Init();
			NewActor->SetActorPosition(NewPos);

			this->ActiveActor.push_back(NewActor);
			return dynamic_cast<TargetT*>(NewActor);
		}
		return nullptr;
	}

	

	World();
	~World();
};

