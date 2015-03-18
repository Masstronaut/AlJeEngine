
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
#include <sstream>
#include <cstdlib> // rand, srand
#include <time.h> // seeding rand


namespace AlJeEngine
{
  extern Engine* ENGINE;

  // Select your engine demo project here!
  namespace Demo
  {
    enum Demo
    {
      Pretzel,
      FireBall,
    };
  } // Demo

  static Demo::Demo DemoToUse = Demo::FireBall;

  namespace Systems
  {

      
    void Test::Init()
    {
      // Register for drawable objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);

      switch (DemoToUse)
      {
      case (Demo::Pretzel):
        PretzelInit(200);
        break;
      case (Demo::FireBall):
        FireBallInit(200);
        break;
      default:
        break;
      }
      
    }

    void Test::Update(float dt)
    {
      switch (DemoToUse)
      {
      case(Demo::Pretzel) :
        PretzelDemo(dt);
        break;
      case(Demo::FireBall) :
        FireBallDemo(dt);
        break;
      default:
        break;
      }
    }

    void Test::Shutdown()
    {

    }

    void Test::PretzelInit(unsigned count)
    {
      // Get a reference to the "Game World" space so that we can add an object to it.
      Space& gameworld = ENGINE->GetSpace("Game World");

      // Clear out any existing objects
      gameworld.Clear();

      // Use the factory to create an object matching the "Box" archetype.
      EntityPtr testObject = ENGINE->Factory().create("Box Particle");

      // Add the object we created to the game world space.
      gameworld.AddEntity(testObject);

      // repeat the process for a few more objects
      for (unsigned i = 0; i < count; ++i)
      {
        EntityPtr entity;
        std::ostringstream name;
        if (i % 2)
        {
          // Create an entity from the "Box" archetype.
          entity = ENGINE->Factory().create("Box Particle");
          // Create a string stream to generate a name for the entity.
          name << "Box Particle " << i / 2;
        }
        else
        {
          entity = ENGINE->Factory().create("Circle Particle");
          name << "Circle Particle " << i / 2 + 1;
        }
        // Set the generated name.
        entity->SetName(name.str());

        // Add the object to the game world.
        gameworld.AddEntity(entity);
      }
    }

    void Test::PretzelDemo(float dt)
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

        sprite->_color.a += rotSpeed * dt * 0.005f;
        if (sprite->_color.a > 1.f)
          sprite->_color.a = 0.f;

      }
    } // PrezelDemo

    void Test::FireBallInit(unsigned count)
    {
      // Seed the RNG
      srand(time(NULL));

      // Get a reference to the "Game World" space so that we can add an object to it.
      Space& gameworld = ENGINE->GetSpace("Game World");

      // Clear out any existing objects
      gameworld.Clear();

      for (unsigned i = 0; i < count; ++i)
      {
        EntityPtr entity;
        std::ostringstream name;

        // Create an entity from the "Box" archetype.
        entity = ENGINE->Factory().create("Box Particle");

        // reduce the scale of the particle so it's a bit smaller
        entity->GET_COMPONENT(Transform)->scale = glm::vec2(0.5f, 0.5f);

        // Set the particle properties
        ParticlePtr particle = entity->GET_COMPONENT(Particle);
        float xvel = static_cast<float>((rand() % 10000) - 5000) / 10000.f;
        float yvel = static_cast<float>((rand() % 10000) - 5000) / 10000.f;
        particle->velocity = glm::normalize(glm::vec2(xvel, yvel));


        float r = static_cast<float>(rand() % 1000) / 1000.f;
        float g = r - static_cast<float>(rand() % 1000) / 1000.f;
        entity->GET_COMPONENT(Sprite)->_color = glm::vec4(r, g, 0.f, 1.f);
        // Create a string stream to generate a name for the entity.
        name << "Fire Particle " << i / 2;
        // Set the generated name.
        entity->SetName(name.str());

        // Add the object to the game world.
        gameworld.AddEntity(entity);
      }
    }

    void Test::FireBallDemo(float dt)
    {
      timeAccumulator += dt;
      if (timeAccumulator > 1.f / 60.f)
      {
        FireBallSpawn(25);
        timeAccumulator -= 1.f / 60.f;
      }

      EntityVec deadParticles;

      for (auto &entity : _entities)
      {
        TransformPtr transform = entity->GET_COMPONENT(Transform);
        ParticlePtr particle = entity->GET_COMPONENT(Particle);

        particle->lifetime -= dt;
        
        if (particle->lifetime <= 0.f)
        {
          deadParticles.push_back(entity);
          continue;
        }
        
        transform->position += particle->velocity * (rand() % 500 * dt);
        if(particle->lifetime <= 1.5f)
        transform->scale -= dt / 2.f;// *0.5f;
      }
      for (auto &it : deadParticles)
        ENGINE->GetActiveSpace().RemoveEntity(it);


    }

    void Test::FireBallSpawn(unsigned count)
    {
      // Get a reference to the "Game World" space so that we can add an object to it.
      Space& gameworld = ENGINE->GetSpace("Game World");

      // Clear out any existing objects
      //gameworld.Clear();

      for (unsigned i = 0; i < count; ++i)
      {
        EntityPtr entity;
        std::ostringstream name;

        // Create an entity from the "Box" archetype.
        entity = ENGINE->Factory().create("Box Particle");

        // reduce the scale of the particle so it's a bit smaller
        entity->GET_COMPONENT(Transform)->scale = glm::vec2(0.5f, 0.5f);

        // Set the particle properties
        ParticlePtr particle = entity->GET_COMPONENT(Particle);
        float xvel = static_cast<float>((rand() % 10000) - 5000) / 10000.f;
        float yvel = static_cast<float>((rand() % 10000) - 5000) / 10000.f;
        particle->velocity = glm::normalize(glm::vec2(xvel, yvel));
        
        float r = static_cast<float>(rand() % 1000) / 1000.f;
        float g = r - static_cast<float>(rand() % 1000) / 1000.f;
        entity->GET_COMPONENT(Sprite)->_color = glm::vec4(r,g,0.f,1.f);

        // Create a string stream to generate a name for the entity.
        name << "Fire Particle " << i / 2;
        // Set the generated name.
        entity->SetName(name.str());

        // Add the object to the game world.
        gameworld.AddEntity(entity);
      }
    }



  } // Systems

} // AlJeEngine