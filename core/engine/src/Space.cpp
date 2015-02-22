
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

  EntityVec Space::GetEntities(mask m) const
  {
	  EntityVec matches;

    // search for entities that fit the mask
    for (auto it : _entities)
      if (it->CheckMask(m))
        matches.push_back(it);
    return matches;
  }

  void Space::RemoveEntity(EntityPtr in)
  {
	  for (auto it : _entities)
	  {
		  if (it == in)
		  {
			  it.reset();
			  it = _entities.back();
			  _entities.pop_back();
			  return;
		  }

	  }
	  throw ("Tried to remove an entity that doesn't exist.\n");
  }

  void Space::Clear()
  {
    _entities.clear();
  }




}; // AlJeEngine

