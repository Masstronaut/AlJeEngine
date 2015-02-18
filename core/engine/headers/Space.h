
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
    Space(std::string &name) : _name(name) {}

#pragma message ("Implement the functions in Space")
    EntityPtr CreateEntity();

    void PopulateEntities(SystemPtr) const;
    EntityVec& GetEntities(mask) const;
    void RemoveEntity(EntityPtr);
    

    const std::string& Name() const { return _name; }
  private:
    std::string _name;
    EntityVec _entities;
  };

}; // AlJeEngine