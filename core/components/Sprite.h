

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <string>
#include "../../lib/math/glm/glm.hpp"
#include "../engine/headers/Component.h"
#include "../systems/Graphics/headers/GLShader.h"

namespace AlJeEngine
{
  class Sprite : public Component
  {
  public:
    Sprite() : Component(EC_Sprite, MC_Sprite) {}

    glm::vec4 _color = { 0.0f, 1.0f, 0.0f, 1.f };

    std::string _shaderName = "Box";
    


  };


  typedef std::shared_ptr<Sprite> SpritePtr;

}; // namespace AlJe