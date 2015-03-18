
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
      for (unsigned i = 0; i < 200; ++i) 
      {
        EntityPtr entity = ENGINE->Factory().create("Box");
        gameworld.AddEntity(entity);
      }
    }

    void Test::Update(float dt)
    {
      glm::vec2 prevObjPosition = { 0.0f, 0.0f };

      bool firstObject = true;
      float prevRot = -1.f;
      float rotSpeed = 0.5f;
      for (auto &it : _entities)
      {
        TransformPtr transform = it->GET_COMPONENT(Transform);
        glm::vec2* position = &transform->position;

        if (firstObject)
        {
          firstObject = false;
          prevRot = transform->rotation;
          transform->rotation = prevRot + dt * rotSpeed;
        }
        else
        {
          transform->rotation += dt * rotSpeed;

        }

        rotSpeed += .5f;


        position->x = (prevObjPosition.x - 10.0f * -cosf(transform->rotation));
        position->y = (prevObjPosition.y + 10.0f * sinf(transform->rotation));

        prevObjPosition = { position->x, position->y };


        // Let's make them look more interesting too!
        SpritePtr sprite = it->GET_COMPONENT(Sprite);
        sprite->_color.r += rotSpeed * dt * 0.005f;
        if (sprite->_color.r > 1.f)
          sprite->_color.r = 0.f;

        sprite->_color.g -= rotSpeed * dt * 0.005f;
        if (sprite->_color.g < 0.f)
          sprite->_color.g = 1.f;

      }
    }

    void Test::Shutdown()
    {

    }



  } // Systems

} // AlJeEngine