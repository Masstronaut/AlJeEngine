

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
  class Bullet : public Component
  {
  public:
    Bullet() : Component(EC_Bullet, MC_Bullet)
                  {
                  }

    float damage = 100.f;
  };

  typedef std::shared_ptr<Bullet> BulletPtr;

}; // namespace AlJe