

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
  class Lifetime : public Component
  {
  public:
    Lifetime() : Component(EC_Lifetime, MC_Lifetime)
                  {
                  }

    float lifetime = 1.f;
  };

  typedef std::shared_ptr<Lifetime> LifetimePtr;

}; // namespace AlJe