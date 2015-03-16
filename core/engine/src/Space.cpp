
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
  }

    EntityPtr Space::CreateEntity()
  {
    _entities.push_back(std::shared_ptr<Entity>(new Entity));
    return _entities.back();
  }

  EntityPtr Space::CreateCamera()
  {
    if (_camera.get() == nullptr)
    {
      // Use the factory to create the default camera object.
      EntityPtr camera = ENGINE->Factory().create("DefaultCamera");
      _entities.push_back(camera);
      return camera;
    }
    return _camera;
  }

  EntityPtr Space::GetCamera()
  {
    if (_camera.get() != nullptr)
    {
      return _camera;
    }
    
    return CreateCamera();
  }


  void Space::PopulateEntities(SystemPtr sys) const
  {
    // clear out the old entities
    sys->_entities.clear();
    
    for (auto &it : _entities)
    {
      // add any entities living in this space that fit the system to the system's cache.
      mask m = sys->Mask();
      if (it->CheckMask(m))
        sys->_entities.push_back(it);
    }
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

