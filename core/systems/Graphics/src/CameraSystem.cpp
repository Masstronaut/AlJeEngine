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
        //Getting the transform component on the object
        TransformPtr transform = it->GET_COMPONENT(Transform);
        //Getting the camera component on the object
        CameraPtr camera = it->GET_COMPONENT(Camera);

        WindowSDLPtr window = GETSYS(WindowSDL);
        //Perspective of the camera, read more at 
        //http://www.songho.ca/opengl/gl_projectionmatrix.html
        camera->_pespective = glm::perspectiveFov(camera->_fieldOfView, 
                                                  transform->scale.x, 
                                                  transform->scale.y, 
                                                  camera->_nearPlane, 
                                                  camera->_farPlane);

        //Orthographic projection for the camera, read more at
        //http://www.songho.ca/opengl/gl_projectionmatrix.html
        camera->_ortho = glm::ortho(transform->position.x - transform->scale.x * 0.5f,
                                    transform->position.x + transform->scale.x * 0.5f,
                                    transform->position.y - transform->scale.y * 0.5f,
                                    transform->position.y + transform->scale.y * 0.5f, 
                                    camera->_nearPlane,
                                    camera->_farPlane);

        //View matrix for the camera, read more at 
        //http://3dgep.com/understanding-the-view-matrix/
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