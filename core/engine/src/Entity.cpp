
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include <cassert>
#include <memory>
#include "../headers/Entity.h"
#include "../../components/ComponentsInclude.h"

namespace AlJeEngine
{

  void Entity::AddComponent(std::shared_ptr < Component > component)
  {
    // If this evaluates to 0, there is already a component of the specified type.
    // Adding multiple instances of one component is not support.
    // The program will terminate.
    assert(_components[component->_type].get() == nullptr);

    _components[component->_type] = component;

    // Add the component's mask to the entity.
    _mask |= component->_mask;

    // If the component was a collider we want to set the Entity's collider type.
    if (component->_type == EC_BoxCollider || component->_type == EC_CircleCollider)
    {
      if (_collider != EC_None)
        throw std::logic_error("Cannot add a collider to an object that already has a collider.");
      else
        _collider = component->_type;

    }
  }


  void Entity::RemoveComponent(EnumeratedComponent ec)
  {
    /*
    // This is optional, and will terminate if the user tries to remove a component,
    // but no component of that type is on this entity.
    assert(_components[ec] != nullptr)
    */
    if (_components[ec])
    {
      // remove the component's mask from the entity mask.
      _mask &= ~(_components[ec]->_mask);

      // release the component from the shared_ptr for it.
      _components[ec].reset();
    }

    if (ec == EC_BoxCollider || ec == EC_CircleCollider)
      _collider = EC_None;

  }

  bool Entity::HasComponent(EnumeratedComponent ec)
  {
    // It must be explicitly cast, as it does not allow implicit conversions.
    return static_cast<bool>(_components[ec]);
  }

  mask Entity::Mask()
  {
    return _mask;
  }

  EnumeratedComponent Entity::Collider()
  {
    return _collider;
  }

  bool Entity::CheckMask(mask m)
  {
	  return ((_mask & m) == m);
  }

}; //AlJeEngine
