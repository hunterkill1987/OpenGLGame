#include "stdafx.h"
#include "World.h"

World* World::Instance = nullptr;

World* World::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new World();

	}
	return Instance;
}

void World::Update(float DeltaTime)
{
	for (Actor* ActorItr:GetActorsItr())
	{
		if (ActorItr->IsAlive())
		{
			ActorItr->Update(DeltaTime);
		}
	}

	ActiveActor.erase(std::remove_if(ActiveActor.begin(),
									 ActiveActor.end(),
									 &World::RemoveActor
									),
									ActiveActor.end()
									);
}
bool World::RemoveActor(Actor* CheckActor)
{
	return World::GetInstance()->CheckActorIsAliave(CheckActor);
}
bool World::CheckActorIsAliave(Actor* CheckActor)
{
	if (!CheckActor->IsAlive())
	{
		DeadActor.push_back(CheckActor);
		return true;
	}
	return false;
}
World::World()
{

	ActiveActor.reserve(PoolSize);
	DeadActor.reserve(PoolSize);
	for (int i = 0; i < PoolSize; i++)
	{
		DeadActor.push_back(new Actor());
	}
	Engine::GetInstance()->GetEventManager()->Bind(this, &World::ChangeSpawnTime, "SpawnTime");
	Engine::GetInstance()->GetEventManager()->Bind(this, &World::OnRestart, "Restart");

	MaxInterval = 1.5f;
	MinInterval = 0.1f;
	CurrentInterval = MaxInterval;
	DeltaInterval = 0.001f;
 
}

void World::ChangeSpawnTime()
{
	if (LocalPlayer->IsAlive())
	{
		CurrentInterval -= DeltaInterval;
		CurrentInterval = Engine::GetInstance()->Clamp<float>(CurrentInterval, MinInterval, MaxInterval);
		
		Engine::GetInstance()->GetEventManager()->SetTimer("AsteroidSpawner", CurrentInterval);
	}
}

void World::OnRestart()
{
	Engine::GetInstance()->GetEventManager()->SetTimer(this, &World::RestartGame, 0.6f, false, "RestartGame");
}

void World::RestartGame()
{
	CurrentInterval = MaxInterval;
	Engine::GetInstance()->GetEventManager()->SetTimer("AsteroidSpawner", MaxInterval);
	ActiveActor.erase(ActiveActor.begin(), ActiveActor.end());
	Init();
}

const std::vector<Actor*> World::GetActorsItr()
{
	return ActiveActor;
}

void World::Init()
{
	LocalPlayer = SpawnActor<Player>(glm::vec3(0.f,-2.5f,-7.f), nullptr);

	if (!Engine::GetInstance()->GetEventManager()->CheckTimer("AsteroidSpawner"))
	{
		Engine::GetInstance()->GetEventManager()->SetTimer(this, &World::SpawnAsteroid, CurrentInterval, true, "AsteroidSpawner");
	}

}

Player* World::GetLocalPlayer()
{
	return LocalPlayer;
}

void World::SpawnAsteroid()
{
	float SpawnPos = Engine::GetInstance()->RandToFloat(-4.f, 4.f);
	SpawnActor<Asteroid>(glm::vec3(SpawnPos, 8.f, -7.f), nullptr);
}

World::~World()
{
}
