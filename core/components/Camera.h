

/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../../lib/math/glm/glm.hpp"
#include "../../lib/math/headers/affmath.h"
#include "../../lib/math/glm/gtc/matrix_transform.hpp"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
  class Camera : public Component
  {
  public:
	  enum CameraView {ORTHOGRAPHIC, PERSPECTIVE};
    Camera() : Component(EC_Camera, MC_Camera)
    {
    }

		//Default average camera values 
	CameraView viewtype;
	float _fieldOfView = 45; 
	float _aspectRatio = 16.0f/9.0f;
	float _nearPlane   = 1.0f;
	float _farPlane    = 100.0f;

	glm::vec3 _upVec   = {0.0f,1.0f,0.0f};
	glm::vec3 _target  = { 0.0f,0.0f,1.0f };
	
	

  private:
	  //Note for me graphics programmer
	  glm::mat4 _pespective;  //glm::perspectiveFov(_fieldOfView, 1280.0f, 720.0f, _nearPlane, _farPlane);
	  glm::mat4 _ortho;       //glm::ortho(0.0f, 1280.0f/*windoWidth*/, 720.0f/*windoHeight*/, 0.0f, 1.0f, 100.0f);
	  glm::mat4 _viewMatrix;   //glm::lookAt(pos of camera, _target, _upVec);
  };

  typedef std::shared_ptr<Camera> CameraPtr;

}; // namespace AlJe