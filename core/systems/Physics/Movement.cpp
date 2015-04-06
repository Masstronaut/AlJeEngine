/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/ComponentsInclude.h"
#include "../SystemsInclude.h"
#include "../../../lib/math/RNG.h" // DEG2RAD
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void Movement::Init()
    {
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_RigidBody);
    }

    void Movement::Update(float dt)
    {
      for (auto entity : _entities)
      {
        TransformPtr transform = entity->GET_COMPONENT(Transform);
        RigidBodyPtr rigidBody = entity->GET_COMPONENT(RigidBody);

        if (rigidBody->speed > rigidBody->maxSpeed)
          rigidBody->speed = rigidBody->maxSpeed;

        //Update the rigidbody based on the object's rotation so that it moves as it turns.
        float direction = transform->rotation * DEG2RAD;
        rigidBody->direction = glm::normalize(glm::vec2(cos(direction), sin(direction)));

        // Apply the velocity to the object.
        transform->position.x += rigidBody->direction.x * rigidBody->speed * dt;
        transform->position.y += rigidBody->direction.y * rigidBody->speed * dt;
      }
    }

    void Movement::Shutdown()
    {

    }

    void Movement::SendMsg(EntityPtr, EntityPtr, Message::Message message)
    {
      float rotationSpeed = 10000.f;
      float thrust = 50.f;

      switch (message)
      {
      case(Message::MV_Up) :
        try
        {
          ApplyThrust(ENGINE->GetActiveSpace()->GetEntityByName("Player"), thrust);
        }
        catch (...)
        {
          // The player doesn't exist.
        }
        break;

      case(Message::MV_Down) :
        try
        {
          ApplyThrust(ENGINE->GetActiveSpace()->GetEntityByName("Player"), thrust);
        }
        catch (...)
        {
          // The player doesn't exist.
        }
        break;

      case(Message::MV_Left) :
        try
        {
          ApplyRotation(ENGINE->GetActiveSpace()->GetEntityByName("Player"), rotationSpeed);
        }
        catch(...)
        {
          // The player doesn't exist.
        }
        break;

      case(Message::MV_Right) :
        try
        {
          ApplyRotation(ENGINE->GetActiveSpace()->GetEntityByName("Player"), -rotationSpeed);
        }
        catch(...)
        {
          // The player doesn't exist.
        }
        break;

      }
    }

    void Movement::ApplyThrust(EntityPtr entity, float thrust)
    {
      RigidBodyPtr rigidBody = entity->GET_COMPONENT(RigidBody);
      rigidBody->speed += thrust * ENGINE->Getdt();
    }

    void Movement::ApplyRotation(EntityPtr entity, float rotationSpeed)
    {
      TransformPtr transform = entity->GET_COMPONENT(Transform);
      transform->rotation += rotationSpeed * ENGINE->Getdt();
    }

  } // Systems

} // AlJeEngine