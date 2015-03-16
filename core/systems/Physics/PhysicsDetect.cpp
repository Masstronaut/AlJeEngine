
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../SystemsInclude.h"
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void PhysicsDetect::Init()
    {
      RegisterComponent(MC_Transform);
    }

    void PhysicsDetect::Update(float dt)
    {
      for (auto &it : _entities)
      {
        TransformPtr transform = it->GET_COMPONENT(Transform);
        glm::vec2* position = &transform->position;



      }
    }

    void PhysicsDetect::Shutdown()
    {

    }


  } // Systems

} // AlJeEngine