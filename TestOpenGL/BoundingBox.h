#pragma once
#include "Actor.h"

class Actor;

class BoundingBox
{
private:

		Actor* Owner;

		glm::vec3 Size;
		glm::vec3 Center;

		std::vector<glm::vec3> GetVertics();
		bool CheckCollision(Actor* OtherActor);
public:

	BoundingBox(Actor* NewOwner);

	void DoCollision();

	glm::vec3 GetCenterOfMass();
	glm::vec3 GetSize() { return this->Size; };
	
	void Resize(glm::vec3 NewSize);

	void AddIgnored(Actor* Ignored);

	~BoundingBox();
};

