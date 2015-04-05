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
      RegisterComponent(MC_Transform);
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

    void BulletController::resolveBulletHit(EntityPtr e1, EntityPtr e2)
    {

      // Deal the bullet's damage
      if (e2->HasComponent(EC_Health))
      {
        e2->GET_COMPONENT(Health)->currentHP -= e1->GET_COMPONENT(Bullet)->damage;
        if (e2->GET_COMPONENT(Health)->currentHP <= 0.f)
        {
          // First object is the one that was killed.
          // Second object is the one that killed it.
          ENGINE->SendMsg(e2, e1, Message::MV_ObjectKilled);

          if (e1->HasComponent(EC_Parent))
          {
            // Update the shooter's hit counter
            if (e1->GET_COMPONENT(Parent)->parent->HasComponent(EC_Weapon))
            {
              e1->GET_COMPONENT(Parent)->parent->GET_COMPONENT(Weapon)->hits += 1;
            }

            // Update the shooter's score
            if (e1->GET_COMPONENT(Parent)->parent->HasComponent(EC_Score) &&
                e2->HasComponent(EC_Score))
            {
              e1->GET_COMPONENT(Parent)->parent->GET_COMPONENT(Score)->currentScore += e2->GET_COMPONENT(Score)->killScore;
            }

          }

          
        }
      }

      // Destroy the bullet if it can't penetrate objects.
      if (e1->HasComponent(EC_RigidBody) && !e1->GET_COMPONENT(RigidBody)->ghost)
      {
        ENGINE->GetActiveSpace()->RemoveEntity(e1);
      }

    }

  } // Systems

} // AlJeEngine