#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
	ActorMesh = new Mesh("Projectile.obj");
	Engine::GetInstance()->GetEventManager()->SetTimer(this, &Projectile::Die, 0.5f, false,"BulletLifeTime");
}

void Projectile::Init()
{
	Actor::Init();
	SetActorVelocity(glm::vec3(Engine::GetInstance()->RandToFloat(-0.02f, 0.02f), 0.3f, 0.0f));
	FireDirection = glm::vec3(0.f, 1.f, 0.f);
}

void Projectile::OnHit(Actor* HitedActor)
{
	Actor::OnHit(HitedActor);
}

void Projectile::Die()
{
	this->DestroyActor();
}
void Projectile::Update(float DeltaTime)
{
	glm::vec3 velocity = this->GetActorVelocity() + FireDirection * 0.02f * Engine::GetInstance()->GetDeltaTime();
	Actor::Update(DeltaTime);
}

Projectile::~Projectile()
{
}
