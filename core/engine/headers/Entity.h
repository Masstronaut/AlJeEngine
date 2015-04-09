

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
    EnumeratedComponent Collider();

    /*!
    * @brief Allows checking if the entity has all of a set of components.
    * @par This functioned is used by OR-ing together multiple MaskComponent values.
    * An example of this would be CheckMask(MC_Transform | MC_RigidBody).
    * This example would check that the object has both the Transform and Rigidbody components.
    * 
    * @param[in] m The mask of one or more OR-ed MaskComponent enum values.
    *  
    * @return Returns a bool. True if the component has every specified component, false in all other cases.
    */
    bool CheckMask(mask m);

    /*!
    * @brief Getter for the Entity's name.
    *
    * @return Returns a const string reference to the Entity's name.
    */
    const std::string& Name() { return _name; }

    /*!
    * @brief Sets the name of the Entity.
    *
    * @param[in] name The name to set for the Entity.
    */
    void SetName(std::string name) { _name = name; }

#define GET_COMPONENT( type ) \
  GetComponent<type>(EC_##type)

    /*!
    * @brief Allows access to derived components attached to the Entity.
    * @par It is recommended that you use the GET_COMPONENT macro,
    * as it automatically expands the typename into the template call and parameter.
    *
    * @param[in] ec The enum identifier of the component. 
    *
    * @return Returns a shared_ptr containing a derived pointer to the component attached to the Entity.
    */
    template <typename T>
    std::shared_ptr<T> GetComponent(EnumeratedComponent ec);

  private:
    std::string _name;
    mask _mask = MC_Alive;
    EnumeratedComponent _collider = EC_None;
    ComponentPtr _components[EC_Max];
  };


  // Template implementation has to have global visibility.
  // This is because a separate implementation must be generated for each usage.
  template <typename T>
  std::shared_ptr<T> Entity::GetComponent(EnumeratedComponent ec)
  {
    // Verify that this component type is attached to the Entity so that the user doesn't try to read invalid memory.
    assert(_components[ec]);
    return std::static_pointer_cast<T>(_components[ec]);
  }

  // typedef magic! AKA laziness
  typedef std::shared_ptr< Entity > EntityPtr;
  typedef std::vector< EntityPtr > EntityVec;
#pragma endregion
}; // AlJeEngine