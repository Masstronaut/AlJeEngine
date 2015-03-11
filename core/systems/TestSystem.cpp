
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "TestSystem.h"
#include "../engine/headers/Engine.h"
#include "../components/Components.h"
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void Test::Init()
    {
      Space& gameworld = ENGINE->GetActiveSpace();
      auto player = gameworld.CreateEntity();
      // Here we use pointers to a base class, but store the derived class.
      // By storing them as the base type they can be stored together.
      player->AddComponent(std::shared_ptr<Component>(new Transform()));
      player->AddComponent(std::shared_ptr<Component>(new BoxCollider()));
    }

    void Test::Update(float dt)
    {

    }

    void Test::Shutdown()
    {

    }



  }; // Systems

}; // AlJeEngine