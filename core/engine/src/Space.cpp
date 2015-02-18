
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/Space.h"
namespace AlJeEngine
{
  EntityPtr Space::CreateEntity()
  {
    _entities.push_back(std::shared_ptr<Entity>(new Entity));
    return _entities.back();
  }
  void Space::PopulateEntities(SystemPtr sys) const
{
    // clear out the old entities
    sys->_entities.clear();
    
    for (auto it : _entities)
      // add any entities living in this space that fit the system to the system's cache.
      if ((it->Mask() & sys->Mask()) == sys->Mask())
        sys->_entities.push_back(it);
}




}; // AlJeEngine

