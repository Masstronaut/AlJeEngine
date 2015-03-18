

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../../lib/math/glm/glm.hpp"
#include "../engine/headers/Component.h"
#include <memory>

namespace AlJeEngine
{
  class Transform : public Component
  {
  public:
    Transform() : Component(EC_Transform, MC_Transform), 
                  position({ 0.f, 0.f }), 
                  scale({ 1.0f, 1.0f }), 
                  rotation(0.f) 
                  {
                  }

    // The transformation data of the object.
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;

    // The matrix that transforms object vertices from object space to world space.
    glm::vec3 objectToWorld;

  };

  typedef std::shared_ptr<Transform> TransformPtr;

}; // namespace AlJe