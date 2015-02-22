/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/GLGraphics.hpp"

namespace AlJeEngine
{

  void GLGraphics::Init(void)       //Initilize SDL
  {
    GLGraphics::CreateMesh();
  }

  void GLGraphics::Update(float dt) //Update everyframe  
  {
  
  }

  void GLGraphics::Shutdown(void)   //called when system is deleated
  {
    GLGraphics::DeleteMesh();
  }
}