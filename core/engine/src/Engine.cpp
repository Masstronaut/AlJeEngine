
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 *
 * @brief The Engine class is the core of the game engine.
 *
 */

#include "../../../lib/timers/ScopeTimer.hpp"
#include "../headers/Engine.h"
#include <iostream>
#include <cassert>
#include "../../systems/SystemsInclude.h"
using std::cout;
using AlJeEngine::Time::ScopeTimer;


namespace AlJeEngine
{
  Engine* ENGINE = nullptr;

  Engine::Engine()
  {
    // There should only ever be one instance of the engine.
    assert(ENGINE == nullptr);
  }

	void Engine::Init()
  {
    // Start your engines!
    _running = true;

    //  Create a world for the engine to run in
    CreateSpace("Game World");
    // set the newly created world to be the active space in the engine.
    SetActiveSpace("Game World");
    // Create a camera for the active space.
    EntityPtr camera = GetSpace("Game World").CreateCamera();

    // test code please ignore
    camera->GET_COMPONENT(Transform)->position = glm::vec2({ 0.5f, 0.5f });

    // Add systems here
    _systems.push_back(SystemPtr(new Systems::WindowSDL));
    _systems.push_back(SystemPtr(new Systems::Test));

    _systems.push_back(SystemPtr(new Systems::PhysicsDetect));

    _systems.push_back(SystemPtr(new Systems::GLGraphics));
    _systems.push_back(SystemPtr(new Systems::Render));

    // initialize all systems
    // using c++11 range-based for loop
    for (auto sys : _systems)
      sys->Init();

  }

  void Engine::Shutdown()
  {
    for (auto sys : _systems)
      sys->Shutdown();

  }

  void Engine::Update(float dt)
  {
    for (auto sys : _systems)
    {
      // Make sure the system has all the entities that meet it's requirements in the active space.
      GetActiveSpace().PopulateEntities(sys);

      sys->Update(dt);
    }

    //cout << "updated: " << static_cast<int>(1.f / dt) << " FPS, " << dt << "ms\n";

  }

  void Engine::mainLoop()
  {
    // manually set the initial dt to prevent weird issues in the first frame.
    dt = 1.f / 60.f;


    while (_running)
    {
      // ScopeTimer is defined in lib/Timers/ScopeTimer.hpp
      // ScopeTimer automatically starts timing when it is created, 
      // and stops when it leaves scope. 
      // It stores the time delta in the input float pointer. Nifty!
      ScopeTimer frameTimer(&dt);

      // Update all the systems
      Update(dt);


    }

  }

  float Engine::FrameTime()
  {
    return dt;
  }

  Space & Engine::CreateSpace(std::string name)
  {
    _spaces.emplace(name, SpacePtr(new Space(name)));
    return GetSpace(name);
  }

  Space & Engine::GetSpace(std::string name)
  {
    // Search for a space with the specified name.
    SpaceMap::iterator it = _spaces.find(name);

    // Check if the space was found or not
    if (it != _spaces.end())
      return *(it->second);

    // If the space wasn't found, throw a range error with a message about what happened.
    throw std::range_error("The specified space does not exist.");
  }

  Space & Engine::SetActiveSpace(std::string name)
  {

    _activeSpace = name;
    return GetActiveSpace();
  }

  Space & Engine::GetActiveSpace()
  {
    auto activeSpace = _spaces.find(_activeSpace);

    return *(activeSpace->second);
  }

  ArchetypeFactory & Engine::Factory()
  {
    // TODO: insert return statement here
    return _archetypeFactory;
  }
  
 



}; //AlJeEngine
