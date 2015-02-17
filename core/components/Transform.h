

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../../lib/math/headers/math.h"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
  class Transform : public Component
  {
  public:
    Transform() : Component(EC_Transform, MC_Transform), 
                  position({ 0.f, 0.f }), 
                  scale({ 1.f, 1.f }), 
                  rotation(0.f) 
                  {
                  }



    Math::mat3 objectToWorld;
    Math::vec2 position;
    Math::vec2 scale;
    float rotation;


  };


}; // namespace AlJe