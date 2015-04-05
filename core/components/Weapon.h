/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../engine/headers/Component.h"
#include <memory>

namespace AlJeEngine
{
  class Weapon : public Component
  {
  public:
    Weapon() : Component(EC_Weapon, MC_Weapon)
                  {
                  }

    float rateOfFire = .5f;
    float shotCooldownRemaining = 0.f;

    unsigned shots = 0;
    unsigned hits = 0;
    unsigned misses = 0;
  };

  typedef std::shared_ptr<Weapon> WeaponPtr;

}; // namespace AlJe