/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/Render.h"
#include "../../../lib/math/glm/gtc/matrix_transform.hpp" //scale, rot, trans, projection
namespace AlJeEngine
{

  Render::Render() : System(std::string("Render System"), ES_Render)
  {
  
  }

}