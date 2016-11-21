#include "stdafx.h"
#include "Player.h"
#include "World.h"

bool Player::keys[1024];

Player::Player()
{
	glfwSetWindowUserPointer(Engine::GetInstance()->window, this);
	glfwSetKeyCallback(Engine::GetInstance()->window, KeyCallback);
	ActorMesh = new Mesh("Player.obj");
	ActorMesh->SetScale(0.6f);
}

void Player::Init()
{
	Actor::Init();
}

void Player::OnHit(Actor* HitedActor)
{
	Actor::OnHit(HitedActor);
	Engine::GetInstance()->GetEventManager()->FireEvent("Restart");
}

void Player::Movemnet()
{
	glm::vec3 PlayerVelocity = GetActorVelocity();
	glm::vec3 NewPlayerVelocity;
	if (keys[GLFW_KEY_LEFT])
	{
		if (GetActorPosition().x >= -4.5f)
		{
			PlayerVelocity.x -= 0.01f;
			NewPlayerVelocity = PlayerVelocity + glm::vec3(-1.f, 0.f, 0.f) * 0.2f * Engine::GetInstance()->GetDeltaTime();
			SetActorVelocity(NewPlayerVelocity);
		}
	}
	else if (keys[GLFW_KEY_RIGHT])
	{
		if (GetActorPosition().x <= 4.5f)
		{
			PlayerVelocity.x += 0.01f;
			NewPlayerVelocity = PlayerVelocity + glm::vec3(1.f, 0.f, 0.f) * 0.2f * Engine::GetInstance()->GetDeltaTime();
			SetActorVelocity(NewPlayerVelocity);
		}
	}
	else
	{
		glm::vec3 dir;
		if (!Engine::IsNear(PlayerVelocity.x, 0.f, 0.05f))
		{
			if (PlayerVelocity.x < 0.f)
			{
				PlayerVelocity.x += 0.02f;
				dir.x = 1.f;
			}
			else if (PlayerVelocity.x > 0.f)
			{
				PlayerVelocity.x -= 0.02f;
				dir.x -= 1.f;
			}
		}
		else  
		{
			PlayerVelocity.x = 0.f;
			dir.x = 0.f;
		}
		NewPlayerVelocity = PlayerVelocity + dir * 0.2f * Engine::GetInstance()->GetDeltaTime();
		SetActorVelocity(NewPlayerVelocity);		
	}
	if (keys[GLFW_KEY_SPACE])
	{
		StartFire();
	}
	else
	{
		StopFire();
	}
}

void Player::StartFire()
{
	if (FireRate > 0.f && Cooldown >= FireRate)
	{
		glm::vec3 StartPos = GetActorPosition();
		StartPos.y += CollisionBox->GetSize().y + 0.02f;
		Projectile* Proj = World::GetInstance()->SpawnActor<Projectile>(StartPos, this);
		Cooldown = 0.f;
	}
	else
	{
		Cooldown += Engine::GetInstance()->GetDeltaTime();
	}
}

void Player::StopFire()
{
	Cooldown = FireRate;
}
void Player::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	void *Data = glfwGetWindowUserPointer(window);
	Player *P = static_cast<Player*>(Data);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Player::Update(float DeltaTime)
{
	Movemnet();
	glm::vec3 CurrentPlayerPos = GetActorPosition();
	CurrentPlayerPos.x = Engine::GetInstance()->Clamp<float>(CurrentPlayerPos.x, (-4.5f), 4.5f);
	
	SetActorPosition(CurrentPlayerPos);

	Actor::Update(DeltaTime);
}

Player::~Player()
{
}
