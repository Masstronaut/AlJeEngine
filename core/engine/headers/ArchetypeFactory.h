/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include <string>
#include <unordered_map>
#include "Entity.h"
#include "Archetypes.h"

namespace AlJeEngine
{

  // The map of archetype names to create functions.
  // This typedef just makes it a smaller, more manageable name.
  typedef std::unordered_map<std::string, CreateArchetypeFn> ArchetypeMap;


  class ArchetypeFactory
  {
  public:
    ArchetypeFactory();

    void addArchetype(std::string archetype, CreateArchetypeFn creator);
    
    EntityPtr create(std::string archetype);

  private:
    ArchetypeMap _archetypes;
  };

}; //AlJeEngine
