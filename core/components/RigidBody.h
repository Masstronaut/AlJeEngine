

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once

#include <memory>
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
  struct RigidBody : public Component
  {

    RigidBody() : Component(EC_RigidBody, MC_RigidBody) {}
    
    bool gravity        = true;
    bool isStatic       = false;
    bool rotationLocked = true;
    bool ghost          = false;

    glm::vec2 direction = { 0.f, 0.f };
    float     speed     =   0.f;
    float     maxSpeed  =  10.f;
  };


  typedef std::shared_ptr<RigidBody> RigidBodyPtr;

}; // namespace AlJe