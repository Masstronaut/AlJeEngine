
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "TestSystem.h"
#include "../engine/headers/Engine.h"
#include "../components/Components.h"
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void Test::Init()
    {
      // Register for drawable objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);


      // Get a reference to the "Game World" space so that we can add an object to it.
      Space& gameworld = ENGINE->GetSpace("Game World");

      // Use the factory to create an object matching the "Box" archetype.
      EntityPtr player = ENGINE->Factory().create("Box");
      player->GET_COMPONENT(Transform)->position = glm::vec2(0.5f, 0.5f);

      // Add the object we created to the game world space.
      gameworld.AddEntity(player);

      // repeat the process for a few more objects
      for (float i = -0.5f; i < 0.5f; i += 0.25f)
      {
        EntityPtr entity = ENGINE->Factory().create("Box");
        entity->GET_COMPONENT(Transform)->position = glm::vec2(i, i);
        gameworld.AddEntity(entity);
      }
    }

    void Test::Update(float dt)
    {
      for (auto &it : _entities)
      {
        TransformPtr transform = it->GET_COMPONENT(Transform);
        glm::vec2* position = &transform->position;

        transform->rotation += dt * 1.5f;

        position->x = (0.f - 3.0f * -cosf(transform->rotation));

        position->y = (0.f + 3.0f * sinf(transform->rotation));
        //transform->position.x = 50.f * cosf(10.f / __PI__) * dt;
        //transform->position.y = 50.f * cosf(10.f / __PI__) * dt;


      }
    }

    void Test::Shutdown()
    {

    }



  } // Systems

} // AlJeEngine