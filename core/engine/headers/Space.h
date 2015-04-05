
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
    Space(std::string &name);


    void Update(float dt);

    void AddSystem(SystemPtr);
    void RemoveSystem(std::string);

    EntityPtr CreateEntity();

    // Creates a camera for the space.
    EntityPtr CreateCamera();

    // Access the camera for the space.
    EntityPtr GetCamera();

    void PopulateEntities(SystemPtr) const;

    EntityVec GetEntities(mask) const;

    EntityPtr GetEntityByName(std::string);

    void RemoveEntity(EntityPtr);
    void AddEntity(EntityPtr);
    // Removes all Entities and systems from the space.
    void Clear();

    // Allows read-only access to the Space's name.
    const std::string& Name() const { return _name; }

  private:
    std::string _name;
    EntityVec _entities;
    EntityPtr _camera;

    SystemVec _systems;
    // Spaces should never be default or copy constructed. Only construction should be via name.
    Space() = delete;
    Space(Space &space) = delete;
  };

  typedef std::shared_ptr<Space> SpacePtr;


}; // AlJeEngine