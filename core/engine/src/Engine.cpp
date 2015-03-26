
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
    ENGINE = this;
  }

	void Engine::Init()
  {
    // Start your engines!
    _running = true;

    // Add systems to the engine here
    _systems.push_back(SystemPtr(new Systems::WindowSDL));
    _systems.push_back(SystemPtr(new Systems::Test));

    _systems.push_back(SystemPtr(new Systems::PhysicsDetect));

    _systems.push_back(SystemPtr(new Systems::CameraSystem));
    _systems.push_back(SystemPtr(new Systems::GLGraphics));


    //  Create a world for the engine to run in:
    SpacePtr gameworld = CreateSpace("Game World");
    // set the newly created world to be the active space in the engine:
    SetActiveSpace("Game World");

    // we need namespace Systems for this macro expansion to work properly. 
    // The system types are not defined outside the Systems namespace, 
    // and using Systems::SystemName would cause the macro to incorrectly expand into:
    // ENGINE->GetSystem<Systems::SystemName>(ES_Systems::SystemName). The parameter would be invalid.
    using namespace Systems;

    // Specify which systems should update for this space. The order they are added in is the order they will update in, so be careful!
    //gameworld->AddSystem(GETSYS(Test));
    gameworld->AddSystem(GETSYS(PhysicsDetect));
    gameworld->AddSystem(GETSYS(CameraSystem));
    gameworld->AddSystem(GETSYS(GLGraphics));


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
    // Update the window management system. It is responsible for the window and input.
    using Systems::WindowSDL;
    GETSYS(WindowSDL)->Update(dt);

    // Signal to graphics that we are beginning a new frame.
    using Systems::GLGraphics;
    GETSYS(GLGraphics)->newFrame();

    for (auto space = _spaces.begin(); space != _spaces.end(); ++space)
    {
      // Set this space as the active one. Whenever a system wants access to it, it will be correct.
      SetActiveSpace(space->first);
      
      // The space will fill all the systems with the relevant entities and have them update.
      space->second->Update(dt);
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

  SpacePtr Engine::CreateSpace(std::string name)
  {
    _spaces.emplace(name, SpacePtr(new Space(name)));
    return GetSpace(name);
  }

  SpacePtr Engine::GetSpace(std::string name)
  {
    // Search for a space with the specified name.
    SpaceMap::iterator it = _spaces.find(name);

    // Check if the space was found or not
    if (it != _spaces.end())
      return it->second;

    // If the space wasn't found, throw a range error with a message about what happened.
    throw std::range_error("The specified space does not exist.");
  }

  SpacePtr Engine::SetActiveSpace(std::string name)
  {

    _activeSpace = name;
    return GetActiveSpace();
  }

  SpacePtr Engine::GetActiveSpace()
  {
    auto activeSpace = _spaces.find(_activeSpace);

    return activeSpace->second;
  }

  ArchetypeFactory & Engine::Factory()
  {
    return _archetypeFactory;
  }

  void Engine::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
  {
    for (auto &it : _systems)
    {
      it->SendMsg(e1, e2, message);
    }
  }

  GamestatePtr Engine::CurrentState() const
  {
    return _gamestates.top();
  }

  void Engine::PushGamestate(GamestatePtr GS)
  {
    _gamestates.push(GS);
    GS->Init();
  }

  void Engine::PopGamestate()
  {
    GamestateType GST = _gamestates.top()->State();
    _gamestates.top()->Shutdown();
    _gamestates.pop();
    if (_gamestates.size())
      _gamestates.top()->PoppedTo(GST);
    else // There are no remaining Gamestates. The game will now exit.
      Stop();
  }
  
 



}; //AlJeEngine
