
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include <cassert>

#include "../headers/Entity.h"

void Entity::AddComponent ( std::shared_ptr < Component > component )
{
  // If this evaluates to 0, there is already a component of the specified type.
  // Adding multiple instances of one component is not support.
  // The program will terminate.
  assert(_components[component->_type] != NULL);

  _components[component->_type] = component;

  // Add the component's mask to the entity.
  _mask |= component->_mask;
}


void Entity::RemoveComponent ( EnumeratedComponent ec )
{
  /*
  // This is optional, and will terminate if the user tries to remove a component,
  // but no component of that type is on this entity.
  assert(_components[ec] == NULL)
  */
  if(_components[ec])
  {
    // remove the component's mask from the entity mask.
    _mask &= ~(_components[ec]->_mask);

    // release the component from the shared_ptr for it.
    _components[ec].reset();
  }


}

bool Entity::HasComponent ( EnumeratedComponent ec )
{
  // It must be explicitly cast, as it does not allow implicit conversions.
  return static_cast<bool>(_components[ec]);
}

mask Entity::Mask()
{
  return _mask;
}
