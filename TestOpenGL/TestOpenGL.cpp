// TestOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Engine.h"
#include "World.h"

using namespace std;

void main(int argc, char** argv)
{       
	Engine* GEngine = Engine::GetInstance();

	World* GWorld = World::GetInstance();

	if (GWorld != nullptr)
	{
		GWorld->Init();
	}
       
	while (!glfwWindowShouldClose(GEngine->window))
	{
		GWorld->Update(GEngine->GetDeltaTime());
		GEngine->GetEventManager()->Update(GEngine->GetDeltaTime());
		GEngine->Render();
	}
}

