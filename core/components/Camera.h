

/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "../../lib/math/glm/glm.hpp"
#include "../../lib/math/glm/gtc/matrix_transform.hpp"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
  namespace Systems
  {
    class CameraSystem;
    class GLGraphics;
    class WindowSDL;
  }
  class Camera : public Component
  {
  public:
	  enum CameraView {CV_ORTHOGRAPHIC, CV_PERSPECTIVE};
    Camera() : Component(EC_Camera, MC_Camera)
    {
    }
    
		//Default average camera values 
    CameraView viewtype  = CV_ORTHOGRAPHIC;
    float _fieldOfView   = 45.0f; 
    float _nearPlane     = .01f;
    float _farPlane      = 100.0f;
    
    glm::vec3 _upVec   = {0.0f,1.0f,0.0f};
    glm::vec3 _target  = { 0.0f,0.0f,0.0f };
	
    friend class Systems::CameraSystem;
    friend class Systems::GLGraphics;
    friend class Systems::WindowSDL;

  private:
	  glm::mat4 _pespective;  
	  glm::mat4 _ortho;       
	  glm::mat4 _viewMatrix;   
  };

  typedef std::shared_ptr<Camera> CameraPtr;

}; // namespace AlJe

#endif
