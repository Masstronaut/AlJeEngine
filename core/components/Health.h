

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
  class Health : public Component
  {
  public:
    Health() : Component(EC_Health, MC_Health)
                  {
                  }

    float currentHP = 100.f;
    float maxHP     = 100.f;
  };

  typedef std::shared_ptr<Health> HealthPtr;

}; // namespace AlJe