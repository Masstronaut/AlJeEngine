
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
      // Get a reference to the "Game World" space so that we can add an object to it.
      Space& gameworld = ENGINE->GetSpace("GameWorld");

      // Use the factory to create an object matching the "Box" archetype.
      EntityPtr player = ENGINE->Factory().create("Box");

      // Add the object we created to the game world space.
      gameworld.AddEntity(player);
    }

    void Test::Update(float dt)
    {

    }

    void Test::Shutdown()
    {

    }



  } // Systems

} // AlJeEngine