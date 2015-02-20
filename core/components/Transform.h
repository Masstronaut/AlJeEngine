

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../../lib/math/glm/glm.hpp"
#include "../../lib/math/headers/affmath.h"
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



    glm::vec3 objectToWorld;
	glm::vec2 position;
	glm::vec2 scale;
    float rotation;


  };


}; // namespace AlJe