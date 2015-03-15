

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
  class Camera : public Component
  {
  public:
    Camera() : Component(EC_Camera, MC_Camera)
    {
    }



    //
    glm::vec2 _upVec = { 0.0, 1.0 };
    glm::vec2 _rightVec = { 1.0, 0.0 };

    // NDC Coordinates of where this camera should draw on the window.
    // The bottom left corner of the window is (-1.0, -1.0)
    // The top right corner of the window is   ( 1.0,  1.0)
    glm::vec2 _bottomLeft = { -1.0, -1.0 };
    glm::vec2 _topRight = { 1.0, 1.0 };


  };


}; // namespace AlJe