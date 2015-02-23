/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../headers/GLGraphics.hpp"
#include "../../../lib/math/glm/gtc/matrix_transform.hpp" //scale, rot, trans, projection
namespace AlJeEngine
{

  void GLGraphics::Init(void)       //Initilize SDL
  {
    GLGraphics::CreateMesh();
    _shader.LoadShaderFile("../.. /Shaders/GLSL/dvert.glsl",
      "../.. /Shaders/GLSL/dfrag.glsl", 0);
    _shader.Compile();
    glm::mat4x4 mymatrix;
    glm::scale(mymatrix,glm::vec3(.2f,.2f,1));
    _shader.AddUniforms("model", mymatrix);

  }

  void GLGraphics::Update(float dt) //Update everyframe  
  {
    Draw();
  }

  void GLGraphics::Shutdown(void)   //called when system is deleated
  {
    GLGraphics::DeleteMesh();
  }
  void GLGraphics::Draw()
  {
    glBindVertexArray(_quadInfo.vao);
    _shader.Use();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
  }
}