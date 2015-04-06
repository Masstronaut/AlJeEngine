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

      
    void WeaponController::Init()
    {
      RegisterComponent(MC_Weapon);
      RegisterComponent(MC_Transform);
    }

    void WeaponController::Update(float dt)
    {
      for (auto entity : _entities)
      {
        WeaponPtr weapon = entity->GET_COMPONENT(Weapon);
        TransformPtr transform = entity->GET_COMPONENT(Transform);

        weapon->shotCooldownRemaining -= dt;

        if (weapon->shotCooldownRemaining <= 0.f)
          weapon->shotCooldownRemaining = 0.f;

      }
    }

    void WeaponController::Shutdown()
    {

    }

    void WeaponController::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {

      
      switch (message)
      {
      case Message::MV_Space:
        try
        {
          FireWeapon(ENGINE->GetActiveSpace()->GetEntityByName("Player"));
        }
        catch (...)
        {
          // The player doesn't exist.
        }
      default:
        break;
      }
    }

    void WeaponController::FireWeapon(EntityPtr entity)
    {
      WeaponPtr weapon = entity->GET_COMPONENT(Weapon);
      TransformPtr transform = entity->GET_COMPONENT(Transform);

      if (weapon->shotCooldownRemaining > 0.f)
        return;

      // Reset the shot cooldown because the weapon should only shoot at its rate of fire.
      weapon->shotCooldownRemaining = weapon->rateOfFire;
      weapon->shots += 1;

      EntityPtr bullet = ENGINE->Factory().create("Bullet");
      bullet->GET_COMPONENT(Parent)->parent = entity;

      // Start the bullet at the shooter's location
      bullet->GET_COMPONENT(Transform)->position = transform->position;
      bullet->GET_COMPONENT(Transform)->rotation = transform->rotation;

      // Set up the physics info for the bullet
      float direction = transform->rotation * DEG2RAD;
      bullet->GET_COMPONENT(RigidBody)->direction = glm::normalize(glm::vec2(cos(direction), sin(direction)));
      bullet->GET_COMPONENT(RigidBody)->speed = weapon->projectileSpeed;

      // Set the duration of the bullet
      bullet->GET_COMPONENT(Lifetime)->lifetime = weapon->projectileLifetime;

      // Add the bullet to the world!
      ENGINE->GetActiveSpace()->AddEntity(bullet);
    }

  } // Systems

} // AlJeEngine