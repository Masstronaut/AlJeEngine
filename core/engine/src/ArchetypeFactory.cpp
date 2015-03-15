/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include "../headers/ArchetypeFactory.h"


namespace AlJeEngine
{
  using namespace Archetypes;

  ArchetypeFactory::ArchetypeFactory()
  {
    // This is where you add the archetype creation functions to the factory.

    addArchetype("DefaultCamera", DefaultCamera);
    addArchetype("Box", BoxGameObject);
  }

  void ArchetypeFactory::addArchetype(std::string archetype, CreateArchetypeFn creator)
  {
    _archetypes[archetype] = creator;
  }

  EntityPtr ArchetypeFactory::create(std::string archetype)
  {
    return _archetypes[archetype]();
  }
}; //AlJeEngine
