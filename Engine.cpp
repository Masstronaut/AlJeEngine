
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 * @brief The Engine class is the core of the game engine.
 * 
 */

#include "Engine.h"

void Engine::Init()
{
  // Add systems here



  // initialize all systems 
  // using c++11 range-based for loop
  for(auto sys : _systems)
    sys->Init();

}

void Engine::Shutdown()
{
  for(auto sys : _systems)
    sys->Shutdown();

}

void Engine::Update(float dt)
{
  for(auto sys : _systems)
  {
    populateEntities(sys);
    sys->Update(dt);
  }

}

void Engine::mainLoop()
{
  while(_running)
  {
    // some frametime logic

    // Update all the systems
    Update(dt);
  }
}