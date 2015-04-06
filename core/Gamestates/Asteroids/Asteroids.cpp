
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "Asteroids.h"
#include "../../engine/headers/Engine.h"
#include "../../components/ComponentsInclude.h"
#include "../../systems/SystemsInclude.h"
#include <math.h> // sin and cos
#include <sstream>
#include <cstdlib> // rand, srand
#include <time.h> // seeding rand
#include "../../lib/math/RNG.h" // randfloat

namespace AlJeEngine
{
  extern Engine* ENGINE;

  using namespace Systems;
  namespace Gamestates
  {

      
    void Asteroids::Init()
    {
      // Register the spaces that should be updated with this system.
      RegisterSpace("Game World");

      // Set which space this gamestate's Update() function should be used with.
      SetLogicalSpace("Game World");

      SpacePtr gameworld = ENGINE->GetSpace("Game World");
      
      // clear out any pre-existing entities and systems from the space.
      gameworld->Clear();


      gameworld->AddSystem(GETSYS(WeaponController));
      gameworld->AddSystem(GETSYS(BulletController));
      gameworld->AddSystem(GETSYS(Movement));

      gameworld->AddSystem(GETSYS(PhysicsDetect));
      gameworld->AddSystem(GETSYS(CameraSystem));
      gameworld->AddSystem(GETSYS(GLGraphics));

      // Register for drawable objects
      RegisterComponent(MC_Transform);

      gameworld->AddEntity(ENGINE->Factory().create("Player"));

      TransformPtr camTrans = gameworld->GetCamera()->GET_COMPONENT(Transform);
  
      camTrans->position = { 0.f, 0.f };
      camTrans->scale = { 16.f, 9.f };
    }

    void Asteroids::Update(float dt)
    {
      TransformPtr cameraTransform = ENGINE->GetActiveSpace()->GetCamera()->GET_COMPONENT(Transform);

      // Calculate the edges of the camera view.
      float leftEdge = cameraTransform->position.x - cameraTransform->scale.x / 2.f;
      float rightEdge = cameraTransform->position.x + cameraTransform->scale.x / 2.f;
      float upEdge = cameraTransform->position.y + cameraTransform->scale.y / 2.f;
      float downEdge = cameraTransform->position.y - cameraTransform->scale.y / 2.f;

      // This loop causes objects to loop around the sides of the map if they would leave it.
      for (auto entity : _entities)
      {
        TransformPtr objTransform = entity->GET_COMPONENT(Transform);

        if (objTransform->position.x < leftEdge)
          objTransform->position.x = rightEdge;

        if (objTransform->position.x > rightEdge)
          objTransform->position.x = leftEdge;

        if (objTransform->position.y < downEdge)
          objTransform->position.y = upEdge;

        if (objTransform->position.y > upEdge)
          objTransform->position.y = downEdge;
      }

      asteroidSpawnTimer -= dt;
      if (asteroidSpawnTimer <= 0.f)
      {
        asteroidSpawnTimer = asteroidSpawnRate;
        SpawnAsteroid();
      }

    }

    void Asteroids::Shutdown()
    {
      if (ENGINE->SpaceExists("Game World"))
      {
        ENGINE->GetSpace("Game World")->Clear();
      }

    }

    void Asteroids::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {
      switch (message)
      {

      case(Message::MV_BackButton) :
        ENGINE->PushGamestate(PauseMenuPtr(new PauseMenu()));
        break;

      case(Message::MV_PopGamestate) :
        ENGINE->PopGamestate();
        break;

      default:
        break;
      }
    }

    void Asteroids::SpawnAsteroid()
    {
      TransformPtr cameraTransform = ENGINE->GetActiveSpace()->GetCamera()->GET_COMPONENT(Transform);

      EntityPtr asteroid = ENGINE->Factory().create("Asteroid");

      asteroid->GET_COMPONENT(Transform)->rotation = RandFloat() * 360.f;

      // It's okay to just do it as a positive value, because it will get wrapped.
      asteroid->GET_COMPONENT(Transform)->position = { RandFloat() * cameraTransform->scale.x + cameraTransform->position.x,
                                                       RandFloat() * cameraTransform->scale.y + cameraTransform->position.y };
      asteroid->GET_COMPONENT(RigidBody)->speed = RandFloat() * asteroid->GET_COMPONENT(RigidBody)->maxSpeed;

      // we do the .25f operations so that there is a minimum scale of .25f.
      float scalefactor = RandFloat() * (asteroid->GET_COMPONENT(CircleCollider)->radius - .25f) + 0.25f;
      asteroid->GET_COMPONENT(Transform)->scale = { scalefactor, scalefactor };
      asteroid->GET_COMPONENT(CircleCollider)->radius = scalefactor;

      ENGINE->GetActiveSpace()->AddEntity(asteroid);
    }

  } // Systems

} // AlJeEngine