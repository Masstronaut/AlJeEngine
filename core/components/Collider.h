

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <vector>
#include "../../lib/math/headers/math.h"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
    enum ColliderType
    {
      circle,
      box,
      poly,
      none
    };

    struct CircleCollider : public Component
    {
      CircleCollider() : Component(EC_CircleCollider, MC_CircleCollider) {}
      float radius = 1.f;
    };
    
    struct BoxCollider : public Component
    {
      BoxCollider() : Component(EC_BoxCollider, MC_BoxCollider) {}
      float height = 1.f;
      float width = 1.f;
    };
  
    struct PolyCollider : public Component
    {
      PolyCollider() : Component(EC_PolyCollider, MC_PolyCollider) {}
      std::vector<Math::vec2> points;
    };


}; // namespace AlJe