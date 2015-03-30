
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "TestSystem.h"
#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../../systems/SystemsInclude.h"
#include <math.h> // sin and cos
#include <sstream>
#include <cstdlib> // rand, srand
#include <time.h> // seeding rand
#include "../../lib/math/RNG.h" // randfloat

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
      Explosion,
    };
  } // Demo

  static Demo::Demo DemoToUse = Demo::FireBall;



  using namespace Systems;
  namespace Gamestates
  {

      
    void Test::Init()
    {
      // Register the spaces that should be updated with this system.
      RegisterSpace("Game World");

      // Set which space this gamestate's Update() function should be used with.
      SetLogicalSpace("Game World");

      // Register for drawable objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);
      RegisterComponent(MC_Particle);


      switch (DemoToUse)
      {
      case (Demo::Pretzel):
        PretzelInit(200);
        break;
      case (Demo::FireBall):
        FireBallInit(200);
        break;
      case Demo::Explosion:
        ExplosionInit(200);
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
      case Demo::Explosion:
        ExplosionDemo(200);
        break;
      default:
        break;
      }
      
      // This is wrapped in a try catch block because it's possible the entity acquired by name doesn't have the necessary components.
      // If that is the case, the try block will encounter and exception, that gets handled by just ignoring the operation and moving on.
      try
      {
        EntityPtr mouse = ENGINE->GetActiveSpace()->GetEntityByName("Mouse");
        mouse->GET_COMPONENT(Transform)->position = GETSYS(WindowSDL)->GetMousePosition();
        mouse->GET_COMPONENT(Transform)->scale = { 10.f, 10.f };
      }
      catch (...)
      {
        
      }
    }

    void Test::Shutdown()
    {

    }

    void Test::PretzelInit(unsigned count)
    {
      // Get a reference to the "Game World" space so that we can add an object to it.
      SpacePtr gameworld = ENGINE->GetSpace("Game World");

      gameworld->GetCamera()->GET_COMPONENT(Transform)->scale = { 160.f, 90.f };
      // Clear out any existing objects
      gameworld->Clear();

      // Use the factory to create an object matching the "Box" archetype.
      EntityPtr testObject = ENGINE->Factory().create("Box Particle");

      // Add the object we created to the game world space.
      gameworld->AddEntity(testObject);

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
        gameworld->AddEntity(entity);
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
      srand(static_cast<unsigned>(time(NULL)));

      
      // Set the Particle Demo space as the logical space for this gamestate.
      SetLogicalSpace("Particle Demo");

      // Register the Particle Demo space as a space that should be updated each frame.
      RegisterSpace("Particle Demo");

      // We also won't be using the "Game World" space, so we can deregister it.
      DeRegisterSpace("Game World");
      
      if (ENGINE->SpaceExists("Particle Demo"))
        return;
      
      // Create the space for the demo to run in.
      SpacePtr particleDemo = ENGINE->CreateSpace("Particle Demo");

      // Specify which systems should be updated for this demo.
      particleDemo->AddSystem(GETSYS(CameraSystem));
      particleDemo->AddSystem(GETSYS(GLGraphics));
      // Clear out any existing objects in the space, except the camera.
      particleDemo->Clear();


    }

    void Test::FireBallDemo(float dt)
    {

      for (auto &entity : _entities)
      {
        TransformPtr transform = entity->GET_COMPONENT(Transform);
        ParticlePtr particle = entity->GET_COMPONENT(Particle);

        float xvel = (RandFloat() * 5.f - 2.5f);
        particle->velocity.x = xvel * 2.f;



        // Uncomment this when rotation is working properly.
        transform->rotation += RandFloat() * 20.f - 10.f;

        if (particle->lifetime <= 1.0f)
        {
          // Uncomment these when scaling is working correctly!
          transform->scale.x -= 3.f* dt ;// *0.5f;
          transform->scale.y -= 3.f* dt;// *0.5f;
        }


        if (particle->lifetime <= 0.f)
        {
          ENGINE->GetActiveSpace()->RemoveEntity(entity);
          continue;
        }
        transform->position.x += particle->velocity.x * dt;// * 5.f ;
        transform->position.y += particle->velocity.y * dt;
        particle->lifetime -= dt;
      }

      timeAccumulator += dt;
      //if (timeAccumulator > 1.f / 60.f)
      {
        FireBallSpawn(50);
        timeAccumulator -= 1.f / 60.f;
      }

    }

    void Test::FireBallSpawn(unsigned count)
    {
      // Get a reference to the "Game World" space so that we can add an object to it.
      SpacePtr gameworld = ENGINE->GetSpace("Particle Demo");

      glm::vec2 mousepos = GETSYS(WindowSDL)->GetMousePosition();

      for (unsigned i = 0; i < count; ++i)
      {
        // get a degree anywhere in a circle (0 through 360)
        float angle = RandFloat() * 360.f;

        float scale = RandFloat() * 80.f;

        glm::vec2 startPos = { cosf(angle) * scale + mousepos.x, sinf(angle) * scale + mousepos.y };

        glm::vec2 velocity = { 0.f, RandFloat() * 8.f - 16.f };
        float lifetime = RandFloat() * 2.f;

        EntityPtr entity = ENGINE->Factory().create("Fire Particle");

        entity->GET_COMPONENT(Transform)->scale = glm::vec2(3.5f, 3.5f);
        entity->GET_COMPONENT(Transform)->position = startPos;
        entity->GET_COMPONENT(Transform)->rotation = 0.f;
        entity->GET_COMPONENT(Particle)->velocity = velocity;
        entity->GET_COMPONENT(Particle)->lifetime = lifetime;

        // Create a string stream to generate a name for the entity.
        std::ostringstream name;
        name << "Fire Particle " << i / 2;
        // Set the generated name.
        entity->SetName(name.str());

        // Add the object to the game world.
        gameworld->AddEntity(entity);
      }

    }
    void Test::ExplosionInit(unsigned count)
    {
      SpacePtr gameworld = ENGINE->GetSpace("Game World");
  
      gameworld->Clear();

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
        gameworld->AddEntity(entity);
      }
    }
    void Test::ExplosionDemo(float dt)
    {
      timeAccumulator += dt;
      if (timeAccumulator > 1.f / 60.f)
      {
        ExplosionSpawn(50);
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
        if (particle->lifetime <= 1.5f)
          transform->scale -= dt / 2.f;// *0.5f;
      }
      for (auto &it : deadParticles)
        ENGINE->GetActiveSpace()->RemoveEntity(it);

    }

    void Test::ExplosionSpawn(unsigned count)
    {
      // Get a reference to the "Game World" space so that we can add an object to it.
      SpacePtr gameworld = ENGINE->GetSpace("Game World");
      gameworld->GetCamera()->GET_COMPONENT(Transform)->scale = { 160.f, 90.f };
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
        entity->GET_COMPONENT(Sprite)->_color = glm::vec4(r, g, 0.f, 1.f);

        // Create a string stream to generate a name for the entity.
        name << "Fire Particle " << i / 2;
        // Set the generated name.
        entity->SetName(name.str());

        // Add the object to the game world.
        gameworld->AddEntity(entity);
      }
    }

    void Test::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {
      EntityPtr camera = ENGINE->GetSpace("Particle Demo")->GetCamera();
      switch (message)
      {
      case(Message::MV_Up) :
        camera->GET_COMPONENT(Transform)->position.y += 1000.f * ENGINE->Getdt();
        break;
      case(Message::MV_Down) :
        camera->GET_COMPONENT(Transform)->position.y -= 1000.f * ENGINE->Getdt();
        break;
      case(Message::MV_Left) :
        camera->GET_COMPONENT(Transform)->position.x -= 1000.f * ENGINE->Getdt();
        break;
      case(Message::MV_Right) :
        camera->GET_COMPONENT(Transform)->position.x += 1000.f * ENGINE->Getdt();
        break;

      case(Message::MV_BackButton) :
        ENGINE->PushGamestate(PauseMenuPtr(new PauseMenu()));
        break;

      default:
        break;
      }
    }

  } // Systems

} // AlJeEngine