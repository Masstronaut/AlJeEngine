
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*
* @brief A Space is a world in which game objects can exist and interact.
*
*/

#pragma once
// Language headers
#include <string>
#include <vector>
#include <memory>

// Engine headers
#include "System.h"
#include "Entity.h"
#include "Component.h"


namespace AlJeEngine
{
  class Space
  {
  public:
    Space() : _name(std::string("Unnamed Space")) {}
    Space(std::string &name) : _name(name) {}

    EntityPtr CreateEntity();

    void PopulateEntities(SystemPtr) const;
    EntityVec GetEntities(mask) const;
    void RemoveEntity(EntityPtr);
    
    void Clear();

    const std::string& Name() const { return _name; }
  private:
    std::string _name;
    EntityVec _entities;
  };

}; // AlJeEngine