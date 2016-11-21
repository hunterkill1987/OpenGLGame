#include "stdafx.h"
#include "Asteroid.h"

void Asteroid::Init()
{
	Scale = Engine::GetInstance()->RandToFloat(0.2f,1.2f);
	SetActorVelocity(glm::vec3(0.f,(-0.01f/Scale),0.0f));

	RotationSpeed = Engine::GetInstance()->RandToFloat(0.4f, 1.2f);

	FallDirection = glm::vec3(Engine::GetInstance()->RandToFloat(-0.2f, 0.2f),-1.f,0.f);

	RotationAxis = glm::vec3(
		Engine::GetInstance()->RandToFloat(0.0f, 1.0f),
		Engine::GetInstance()->RandToFloat(0.0f, 1.0f),
		Engine::GetInstance()->RandToFloat(0.0f, 1.0f)
		);

	this->SetActorRotation(RotationAxis);
	if (GetMesh() != nullptr)
	{
		GetMesh()->SetScale(Scale);
	}

	Actor::Init();
}

void Asteroid::Update(float DeltaTime)
{
	glm::vec3 velocity = this->GetActorVelocity() + FallDirection * 0.02f * Engine::GetInstance()->GetDeltaTime();
	this->SetActorVelocity(velocity);

	Player* player = World::GetInstance()->GetLocalPlayer();

	if (player != nullptr)
	{
		glm::vec3 DirToPlayer = glm::normalize(player->GetActorPosition() - GetActorPosition());
		glm::vec3 Check = glm::normalize(player->GetActorPosition()  - glm::vec3(0.f, -1.f, 0.f));

		double Dot = glm::dot(DirToPlayer,Check);
		
		if (Dot < -0.2f)
		{
			DestroyActor();
		}
	}

	this->SetActorRotation(RotationAxis * (GLfloat)glfwGetTime() * RotationSpeed);

	Actor::Update(DeltaTime);
}

void Asteroid::OnHit(Actor* HitedActor)
{	
	if (!dynamic_cast<Asteroid*>(HitedActor))
	{
		if (dynamic_cast<Projectile*>(HitedActor))
		{
	  		Engine::GetInstance()->GetEventManager()->FireEvent("SpawnTime");
		}
		Actor::OnHit(HitedActor);
	}
}
Asteroid::Asteroid()
{
	ActorMesh = new Mesh("Asteroid.obj");
}
Asteroid::~Asteroid()
{
}