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

  GLGraphics::GLGraphics() : System(std::string("GLGraphicsSystem"), ES_GLGraphics)
  {
  
  }
  void GLGraphics::Init(void) //Initilize SDL
  {
    CreateMesh();
    _shader.LoadShaderFile("dvert.glsl", "dfrag.glsl", 0);
    _shader.Compile();
    _shader.FindUniforms("model");

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

    glm::mat4x4 mymatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));

    _shader.UpdateUniforms("model", mymatrix);

      //Clear the color buffer to redraw on the screen.
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glBindVertexArray(_quadInfo.vao);
    _shader.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
  }
}