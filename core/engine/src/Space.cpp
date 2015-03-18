
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/Space.h"
#include "../headers/Engine.h"

namespace AlJeEngine
{
  extern Engine* ENGINE;


  Space::Space(std::string & name): _name(name)
  {
    _camera = CreateCamera();
  }

    EntityPtr Space::CreateEntity()
  {
    _entities.push_back(std::shared_ptr<Entity>(new Entity));
    return _entities.back();
  }

  EntityPtr Space::CreateCamera()
  {
    // Use the factory to create the default camera object.
    EntityPtr camera = ENGINE->Factory().create("DefaultCamera");
    _entities.push_back(camera);
    return camera;
  }

  EntityPtr Space::GetCamera()
  {    
    return _camera;
  }


  void Space::PopulateEntities(SystemPtr sys) const
  {
    // clear out the old entities
    sys->_entities.clear();
    
    if (sys->Mask() != EC_NOOBJECTS)
    {
      for (auto &it : _entities)
      {
        // add any entities living in this space that fit the system to the system's cache.
        mask m = sys->Mask();
        if (it->CheckMask(m))
          sys->_entities.push_back(it);
      } // for all entities in this space
    } // if !EC_NOOBJECTS

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

  void Space::AddEntity(EntityPtr entity)
  {
    _entities.push_back(entity);
  }

  void Space::Clear()
  {
    _entities.clear();
  }




}; // AlJeEngine

