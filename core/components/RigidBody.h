

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

    float density = 1.0f;

    bool gravity = true;
    bool isStatic = false;
    bool rotationLocked = true;
    bool ghost = false;
  };


  typedef std::shared_ptr<RigidBody> RigidBodyPtr;

}; // namespace AlJe