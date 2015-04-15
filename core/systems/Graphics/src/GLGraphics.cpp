/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../../../engine/headers/Engine.h"
#include "../headers/GLGraphics.hpp"
#include "../../../lib/math/glm/gtc/matrix_transform.hpp" //scale, rot, trans, projection, ortho

namespace AlJeEngine
{
  extern Engine* ENGINE;
  namespace Systems
  {

    /*!
    * @brief Ctor for the graphics system
    */
    GLGraphics::GLGraphics() : System(std::string("GLGraphicsSystem"), ES_GLGraphics)
    {

    }

    /*!
    * @brief Initilize everything SDL needs at the start
    */
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
      defaultShader->FindUniforms("view");
      defaultShader->FindUniforms("proj");
      defaultShader->FindUniforms("color");
      
      

      // Add the shader to the ShaderMap.
      addShader("Box", defaultShader);

    }


    /*!
    * @brief Draws everything that is in the entities list with a sprite component
    * @param dt the time per frame use if needed
    */
    void GLGraphics::Update(float dt)    // Update every frame 
    {
      CameraPtr camera = ENGINE->GetActiveSpace()->GetCamera()->GET_COMPONENT(Camera);
      // clear the buffers to begin a new frame.
      //newFrame();
      // The new frame operation is now handled by the Engine::Update(float) function.

      // Enable alpha blending for opacity.
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      
      for (auto &it : _entities)
      {
        DrawEntity(it, camera);
      }
      
    }

    /*!
    * @brief Draws everything that is in the entities list with a sprite component
    * @param Entity the entity that is going to be drawn
    * @param camera the camera used to draw the objects to
    */
    void GLGraphics::DrawEntity(const EntityPtr &Entity, const CameraPtr &camera)
    {
      ShaderPtr shader = _shaders.find(Entity->GET_COMPONENT(Sprite)->_shaderName)->second;

      TransformPtr transform = Entity->GET_COMPONENT(Transform);

      if (shader.get() != nullptr)
      {
        //constructing the matrix of the transform
        glm::mat4x4 object2world;
        object2world = glm::translate(object2world, 
                                      glm::vec3( Entity->GET_COMPONENT(Transform)->position.x,
                                                 Entity->GET_COMPONENT(Transform)->position.y,
                                                 0.0f )
                                     );

        object2world = glm::rotate( object2world, 
                                    transform->rotation * 3.141592f / 180.f, // degrees to radians conversion 
                                    glm::vec3(0.f, 0.f, 1.0f)
                                  );

        object2world = glm::scale(object2world, 
                                  glm::vec3(transform->scale.x,
                                            transform->scale.y,
                                            0.f)
                                 );

        //Updating the uniforms in the shader, has to happen every frame
        shader->UpdateUniforms("model", object2world);

        shader->UpdateUniforms("view", camera->_viewMatrix);
        
        //Switching the camera's projection matrix based on the flag
        switch (camera->viewtype)
        {
        case Camera::CV_ORTHOGRAPHIC:
          shader->UpdateUniforms("proj", camera->_ortho);
          break;
        case Camera::CV_PERSPECTIVE:
          shader->UpdateUniforms("proj", camera->_pespective);
          break;
        }

        shader->UpdateUniforms("color", Entity->GET_COMPONENT(Sprite)->_color);
        
        shader->Use();

        switch (Entity->GET_COMPONENT(Sprite)->mesh)
        {
        case Sprite::QUAD:
          glBindVertexArray(_quadInfo.vao);
          glDrawElements(
            GL_TRIANGLE_STRIP, //Draw Type
            6,                 //Number of points
            GL_UNSIGNED_SHORT, //Data that it is when being read
            nullptr);          
          break;
        case Sprite::CIRCLE:
          glBindVertexArray(_circleInfo.vao);
          glDrawElements(GL_TRIANGLE_FAN, 30000, GL_UNSIGNED_SHORT, nullptr);
          break;
        default:
          glBindVertexArray(_quadInfo.vao);
          glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, nullptr);
          break;
        }
            
      }
    }


    /*!
    * @brief Calls when the system is shutting down
    */
    void GLGraphics::Shutdown(void)  //called when system is deleated
    {
      DeleteMesh();
    }

    
    /*!
    * @brief Gets the shader associated with the shader
    *
    * @param shaderName the name of the shader the user is trying to get
    */
    ShaderPtr GLGraphics::getShader(std::string shaderName)
    {
      // Search for a space with the specified name.
      ShaderMap::iterator it = _shaders.find(shaderName);

      // Check if the space was found or not
      if (it != _shaders.end())
        return it->second;

      // If the shader wasn't found, throw a range error with a message about what happened.
      throw std::range_error("The specified shader does not exist.");
    }

    /*!
    * @brief Adds shaders to the map
    *
    * @param shaderName name of the shader to access from the map
    * @param shader Shader to put in the map
    */
    void GLGraphics::addShader(std::string shaderName, ShaderPtr shader)
    {
      //Adding the shader to the map, .first = shadername .second = shader
      _shaders.emplace(shaderName, shader);
    }

  } // Systems
} // AlJeEngine
