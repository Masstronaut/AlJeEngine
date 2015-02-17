

/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include <cassert>
#include <memory> // automated memory management for components
#include <string>
#include "Component.h"

namespace AlJeEngine
{

  struct Entity
  {
    /**
     * @brief Adds a component to the entity by pointer.
     *
     * @param component Pointer to the component being added to the entity.
     */
    void AddComponent(std::shared_ptr < Component > component);

    /**
     * @brief Removes a component from the entity.
     *
     * @param ec The type of component to remove from the entity.
     */
    void RemoveComponent(EnumeratedComponent           ec);

    /**
     * @brief Checks if the entity has a specific type of component.
     *
     * @param ec The type of component to check for.
     * @return Returns true if the entity has the specified component type, false otherwise.
     */
    bool HasComponent(EnumeratedComponent           ec);

    mask Mask();

#define GET_COMPONENT( type ) \
  GetComponent<type>(EC_##type)

    template <typename T>
    std::shared_ptr<T> GetComponent(EnumeratedComponent           ec);

  private:
    std::shared_ptr<Component> _components[EC_Max];
    const std::string _name;
    mask _mask;
  };


  // Template implementation has to have global visibility.
  // This is because a separate implementation must be generated for each usage.
  template <typename T>
  std::shared_ptr<T> Entity::GetComponent(EnumeratedComponent ec)
  {
    assert(_components[ec]);
    return _components[ec];
  }

}; // AlJeEngine