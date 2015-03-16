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

      // Create the default shader.
      ShaderPtr defaultShader(new GLShader());

      // Load the shader files for the default shader.
      defaultShader->LoadShaderFile("dvert.glsl", "dfrag.glsl", 0);

      // Compile the shaders.
      defaultShader->Compile();

      // Find the variables in the shaders that will be modified by the end-users.
      defaultShader->FindUniforms("model");
      defaultShader->FindUniforms("color");

      // Add the shader to the ShaderMap.
      addShader("Default", defaultShader);

    }
    //Update every frame 
    void GLGraphics::Update(float dt)
    {
      // Clear the color buffer so the screen can be re-drawn.
      glClear(GL_COLOR_BUFFER_BIT);

      // Enable alpha blending for opacity.
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      for (auto &it : _entities)
      {
        DrawEntity(it);
      }
      
    }


    void GLGraphics::DrawEntity(const EntityPtr &Entity)
    {
      ShaderPtr shader = _shaders.find(Entity->GET_COMPONENT(Sprite)->_shaderName)->second;

      TransformPtr transform = Entity->GET_COMPONENT(Transform);

      if (shader.get() != nullptr)
      {
        glm::mat4x4 object2world;
        object2world = glm::scale(object2world, glm::vec3(transform->scale.x,
                                                          transform->scale.y,
                                                          0.f));

        object2world = glm::rotate(object2world, transform->rotation, glm::vec3(0.f, 0.f, 1.f));

        object2world = glm::translate(object2world, glm::vec3(Entity->GET_COMPONENT(Transform)->position.x,
          Entity->GET_COMPONENT(Transform)->position.y,
          0.0f));

        shader->UpdateUniforms("model", object2world);
        shader->UpdateUniforms("color", Entity->GET_COMPONENT(Sprite)->_color);

        glBindVertexArray(_quadInfo.vao);
        shader->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
      }
    }

    //called when system is deleated
    void GLGraphics::Shutdown(void)
    {
      DeleteMesh();
    }
    

    ShaderPtr GLGraphics::getShader(std::string shaderName)
    {
      // Search for a space with the specified name.
      ShaderMap::iterator it = _shaders.find(shaderName);

      // Check if the space was found or not
      if (it != _shaders.end())
        return it->second;

      // If the space wasn't found, throw a range error with a message about what happened.
      throw std::range_error("The specified space does not exist.");
    }

    void GLGraphics::addShader(std::string shaderName, ShaderPtr shader)
    {
      _shaders.emplace(shaderName, shader);
    }

  } // Systems
} // AlJeEngine
