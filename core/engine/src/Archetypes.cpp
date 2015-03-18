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
      camera->SetName("Camera");

      camera->GET_COMPONENT(Transform)->scale = glm::vec2(160.0f, 90.0f);

      return camera;
    }

    EntityPtr BoxGameObject()
    {
      EntityPtr entity(new Entity());

      entity->AddComponent(ComponentPtr(new BoxCollider()));
      entity->AddComponent(ComponentPtr(new RigidBody()));
      entity->AddComponent(ComponentPtr(new Transform()));
      entity->AddComponent(ComponentPtr(new Sprite()));
      entity->SetName("Box Object");

      return entity;
    }
  
    EntityPtr CircleGameObject()
    {
      EntityPtr entity(new Entity());

      entity->AddComponent(ComponentPtr(new CircleCollider()));
      entity->AddComponent(ComponentPtr(new RigidBody()));
      entity->AddComponent(ComponentPtr(new Transform()));
      entity->AddComponent(ComponentPtr(new Sprite()));
      entity->SetName("Circle Object");

      return entity;
    }
  
  } // Archetypes

} //AlJeEngine
