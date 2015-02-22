

/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include <cassert>
#include <memory> // automated memory management for components
#include <vector> // the best data structure ever
#include <string>
#include "Component.h"
#include "../../components/Components.h"

namespace AlJeEngine
{

  // depends for typedef magic
  //#include <vector>
  //#include <memory>
  // typedef magic! AKA laziness
  typedef std::shared_ptr< Component > ComponentPtr;
  typedef std::vector< ComponentPtr > ComponentVec;
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
    void RemoveComponent(EnumeratedComponent ec);

    /**
     * @brief Checks if the entity has a specific type of component.
     *
     * @param ec The type of component to check for.
     * @return Returns true if the entity has the specified component type, false otherwise.
     */
    bool HasComponent(EnumeratedComponent ec);

    /**
    * @brief Gets a copy of the Entity's mask, which is a bitfield of the components attached to it.
    *
    * @return returns a mask of all the components attached to the entity.
    */
    mask Mask();

    /**
    * @brief Gets the collider type of the entity.
    *
    * @return Returns the collider type being used by the Entity.
    */
    ColliderType Collider();

	bool CheckMask(mask m);

#define GET_COMPONENT( type ) \
  GetComponent<type>(EC_##type)

    template <typename T>
    std::shared_ptr<T> GetComponent(EnumeratedComponent ec);

  private:
    ColliderType _collider;
    ComponentPtr _components[EC_Max];
    std::string _name;
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

  // typedef magic! AKA laziness
  typedef std::shared_ptr< Entity > EntityPtr;
  typedef std::vector< EntityPtr > EntityVec;
#pragma endregion
}; // AlJeEngine