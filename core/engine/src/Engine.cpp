
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
#include "..\headers\WindowSDL.h"
using std::cout;
using AlJeEngine::Time::ScopeTimer;

namespace AlJeEngine
{
	
	void Engine::Init()
  {
    // Start your engines!
    _running = true;

    //  Create a world for the engine to run in
    _spaces["Game World"] = Space(std::string("Game World"));


    // Add systems here
    _systems.push_back(SystemPtr(new WindowSDL));


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

    cout << "updated: " << static_cast<int>(1.f / dt) << " FPS, " << dt << "ms\n";

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

  Space & Engine::CreateSpace(std::string & name)
  {
    // TODO: insert return statement here
    _spaces[name] = Space(name);
    return GetSpace(name);
  }

  Space & Engine::GetSpace(std::string &name)
  {
    // TODO: insert return statement here
    return _spaces[name];
  }

  Space & Engine::SetActiveSpace(std::string & name)
  {
    // TODO: insert return statement here
    _activeSpace = name;
    return GetActiveSpace();
  }

  Space & Engine::GetActiveSpace()
  {
    return _spaces[_activeSpace];
  }



}; //AlJeEngine
