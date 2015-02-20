

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <string>
#include "../../lib/math/glm/glm.hpp"
#include "../../lib/math/headers/affmath.h"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
  class Sprite : public Component
  {
  public:
    Sprite() : Component(EC_Sprite, MC_Sprite) {}

    glm::vec4 color;

    std::string shaderName;
    std::string texture;


  };


}; // namespace AlJe