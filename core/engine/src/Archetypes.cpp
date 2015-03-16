/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include "../headers/Archetypes.h"

namespace AlJeEngine
{
  namespace Archetypes
  {
    EntityPtr DefaultCamera()
    {
      EntityPtr camera(new Entity());

      camera->AddComponent(ComponentPtr(new Camera()));
      camera->AddComponent(ComponentPtr(new Transform()));

      return camera;
    }

    EntityPtr BoxGameObject()
    {
      EntityPtr entity(new Entity());

      entity->AddComponent(ComponentPtr(new BoxCollider()));
      entity->AddComponent(ComponentPtr(new Transform()));
      entity->AddComponent(ComponentPtr(new Sprite()));

      return entity;
    }
  
  
  } // Archetypes

} //AlJeEngine
