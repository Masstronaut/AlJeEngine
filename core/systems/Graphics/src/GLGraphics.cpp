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
  namespace Systems
  {

    GLGraphics::GLGraphics() : System(std::string("GLGraphicsSystem"), ES_GLGraphics)
    {

    }
    void GLGraphics::Init(void) //Initilize SDL
    {
      // Register the components needed for graphics.
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);

      CreateMesh();
      ShaderPtr defaultShader(new GLShader());

      defaultShader->LoadShaderFile("dvert.glsl", "dfrag.glsl", 0);
      defaultShader->Compile();
      defaultShader->FindUniforms("model");
      defaultShader->FindUniforms("color");

      _shaders.emplace("Default", defaultShader);

    }
    //Update every frame 
    void GLGraphics::Update(float dt)
    {
      // Clear the color buffer so the screen can be re-drawn.
      glClear(GL_COLOR_BUFFER_BIT);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //Draw();
      
      for (auto &it : _entities)
      {
        DrawEntity(it);
      }
      
    }


    void GLGraphics::DrawEntity(const EntityPtr &Entity)
    {
      ShaderPtr shader = _shaders.find(Entity->GET_COMPONENT(Sprite)->_shaderName)->second;
      glm::mat4x4 object2world;
      object2world = glm::scale(object2world, glm::vec3(Entity->GET_COMPONENT(Transform)->scale.x,
                                                        Entity->GET_COMPONENT(Transform)->scale.y,
                                                        0.f));

      object2world = glm::translate(object2world, glm::vec3(Entity->GET_COMPONENT(Transform)->position.x, 
                                                            Entity->GET_COMPONENT(Transform)->position.y, 
                                                            0.0f));

      shader->UpdateUniforms("model", object2world);
      shader->UpdateUniforms("color", Entity->GET_COMPONENT(Sprite)->_color);

      glBindVertexArray(_quadInfo.vao);
      shader->Use();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }

    //called when system is deleated
    void GLGraphics::Shutdown(void)
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

  } // Systems
} // AlJeEngine
