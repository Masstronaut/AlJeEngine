/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/ComponentsInclude.h"
#include "../SystemsInclude.h"
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void BulletController::Init()
    {
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_CircleCollider);
      RegisterComponent(MC_RigidBody);
      RegisterComponent(MC_Bullet);
      RegisterComponent(MC_Parent);
      RegisterComponent(MC_Lifetime);
    }

    void BulletController::Update(float dt)
    {
      for (auto entity : _entities)
      {
        LifetimePtr lifetime = entity->GET_COMPONENT(Lifetime);
        
        lifetime->lifetime -= dt;

        if (lifetime->lifetime <= 0.f)
        {
          EntityPtr parent = entity->GET_COMPONENT(Parent)->parent;
          if (parent->HasComponent(EC_Weapon))
            parent->GET_COMPONENT(Weapon)->misses += 1;

          ENGINE->GetActiveSpace()->RemoveEntity(entity);
          continue;
        }

      }
    }

    void BulletController::Shutdown()
    {

    }

    void BulletController::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {
      // Verify that an entity was included in the message
      if (!e1 || !e2)
        return;
      
      switch (message)
      {
      case Message::MV_CircleCircle:
        
        if (e1->HasComponent(EC_Bullet))
          resolveBulletHit(e1, e2);

        else if (e2->HasComponent(EC_Bullet))
          resolveBulletHit(e2, e1);
        break;
        
      default:
        break;
      }
    }

    void BulletController::resolveBulletHit(EntityPtr bullet, EntityPtr hitObject)
    {
      // bullets shouldn't hit the object that fired them.
      if (bullet->HasComponent(EC_Parent) && bullet->GET_COMPONENT(Parent)->parent == hitObject)
        return;

      // Deal the bullet's damage
      if (hitObject->HasComponent(EC_Health))
      {
        hitObject->GET_COMPONENT(Health)->currentHP -= bullet->GET_COMPONENT(Bullet)->damage;
        if (hitObject->GET_COMPONENT(Health)->currentHP <= 0.f)
        {
          // First object is the one that was killed.
          // Second object is the one that killed it.
          ENGINE->SendMsg(hitObject, bullet, Message::MV_ObjectKilled);
          ENGINE->GetActiveSpace()->RemoveEntity(hitObject);

          if (bullet->HasComponent(EC_Parent))
          {
            // Update the shooter's hit counter
            if (bullet->GET_COMPONENT(Parent)->parent->HasComponent(EC_Weapon))
            {
              bullet->GET_COMPONENT(Parent)->parent->GET_COMPONENT(Weapon)->hits += 1;
            }

            // Update the shooter's score
            if (bullet->GET_COMPONENT(Parent)->parent->HasComponent(EC_Score) &&
                hitObject->HasComponent(EC_Score))
            {
              bullet->GET_COMPONENT(Parent)->parent->GET_COMPONENT(Score)->currentScore += hitObject->GET_COMPONENT(Score)->killScore;
            }

          }

          
        }
      }

      // Destroy the bullet if it can't penetrate objects.
      if (bullet->HasComponent(EC_RigidBody) && !bullet->GET_COMPONENT(RigidBody)->ghost)
      {
        try
        {
          ENGINE->GetActiveSpace()->RemoveEntity(bullet);
        }
        catch (...)
        {
          // if this code gets executed the bullet probably hit two things at once.
        }
      }

    }

  } // Systems

} // AlJeEngine