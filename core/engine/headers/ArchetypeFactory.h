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
    /*!
    * @brief Constructs the archetype factory, which is used to easily create uniform complex objects.
    */
    ArchetypeFactory();

    /*!
    * @brief Adds an archetype to the factory.
    *
    * @param archetype The name of the archetype.
    * @param creator a function pointer of the CreateArchetypeFn format to the function that creates this archetype.
    * @note A CreateArchetypeFn is a function which returns an EntityPtr but has no parameters.
    */
    void addArchetype(std::string archetype, CreateArchetypeFn creator);
    
    /*!
    * @brief Creates an entity from archetype.
    * 
    * @param archetype The name of the archetype to create.
    *
    * @return Returns a pointer to the Entity that is an instance of the archetype specified.
    * @note The entity is not added to any space, so the caller must do that manually.
    */
    EntityPtr create(std::string archetype);

  private:
    ArchetypeMap _archetypes;
  };

}; //AlJeEngine
