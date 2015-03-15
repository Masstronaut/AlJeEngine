/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/Render.h"
#include "../../../engine/headers/Engine.h"
#include "../../../lib/math/glm/gtc/matrix_transform.hpp" //scale, rot, trans, projection
namespace AlJeEngine
{
  namespace Systems
  {

    extern Engine* ENGINE;

    Render::Render() : System(std::string("Render System"), ES_Render)
    {

    }

    void Render::Init()
    {
      // RegisterComponent(MC_Camera);
      RegisterComponent(MC_Transform);
    }

    void Render::Update(float dt)
    {
      for (auto &it : _entities)
      {
        // do stuff with game objects here
        TransformPtr transform = it->GET_COMPONENT(Transform);

      }
    }

    void Render::Shutdown()
    {

    }

  } // Systems
} // AlJeEngine