

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../engine/headers/Component.h"
#include <memory>

// We must forward declare it inord
class Entity;

namespace AlJeEngine
{
  class Parent : public Component
  {
  public:
    Parent() : Component(EC_Parent, MC_Parent)
                  {
                  }

    std::shared_ptr<Entity> _parent = nullptr;
  };

  typedef std::shared_ptr<Parent> ParentPtr;

}; // namespace AlJe