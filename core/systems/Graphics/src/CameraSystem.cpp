/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../../../components/Components.h"
#include "../../SystemsInclude.h"
#include "../../../engine/headers/Engine.h"
#include "../../../lib/math/glm/gtc/matrix_transform.hpp" //scale, rot, trans, projection
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {


    CameraSystem::CameraSystem() : System(std::string("Camera System"), ES_CameraSystem)
    {

    }

    void CameraSystem::Init()
    {
      RegisterComponent(MC_Camera);
      RegisterComponent(MC_Transform);
    }

    void CameraSystem::Update(float dt)
    {
      for (auto &it : _entities)
      {
        // do stuff with camera here
        
        TransformPtr transform = it->GET_COMPONENT(Transform);
        CameraPtr camera = it->GET_COMPONENT(Camera);

        WindowSDLPtr window = GETSYS(WindowSDL);
       
        camera->_pespective = glm::perspectiveFov(camera->_fieldOfView, 
                               static_cast<float>(transform->scale.x), 
                               static_cast<float>(transform->scale.y), 
                                                  camera->_nearPlane, 
                                                  camera->_farPlane);

        camera->_ortho = glm::ortho(transform->position.x - transform->scale.x * 0.5f,
                                    transform->position.x + transform->scale.x * 0.5f,
                                    transform->position.y - transform->scale.y * 0.5f,
                                    transform->position.y + transform->scale.y * 0.5f, 
                                    camera->_nearPlane,
                                    camera->_farPlane);
        camera->_viewMatrix = glm::lookAt(glm::vec3(transform->position.x, transform->position.y, -10.0f),
                                          camera->_target, 
                                          camera->_upVec);
      }
    }

    void CameraSystem::Shutdown()
    {

    }

  } // Systems
} // AlJeEngine