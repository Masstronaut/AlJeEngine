/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../headers/GLGraphics.hpp"
#include "../../../lib/math/glm/glm.hpp" //vec3,vec2
#include "../../../lib/math/glm/gtc/type_ptr.hpp" //convert glm data type to raw pointers
#include <math.h> //sin cos

struct Quad
{
  glm::vec3 vertices;
  glm::vec2 UV;
};

namespace AlJeEngine 
{
  namespace Systems
  {

    void GLGraphics::CreateMesh()
    {
      //Make a quad on the stack
      Quad GraphicsQuad[] =
      {
        //Position of quad             //UV coordiates of quad
        glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f),//indices 0
        glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f),//indices 1
        glm::vec3(1.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f),//indices 2
        glm::vec3(1.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f) //indices 3    
      };


      //glm::vec3 circleVert[32] = {};
      //for (int i = 0; i < 32; ++i)
      //{
      //  float theta = 2.0f * __PI__ * ((float)i / (float)32);
      //  circleVert[i].x = cos(theta);
      //  circleVert[i].y = sin(theta);
      //}

      glm::vec3 circleMesh[30000];
      for (int i = 0; i < 30000; ++i)
      {
        float angle = 2.0f * __PI__ * ((float)i / 30000.0f);
        circleMesh[i].x = cos(angle);
        circleMesh[i].y = sin(angle);
      }
      GLushort circleIndicies[30000];
      for (int i = 0; i < 30000; ++i)
      {
        circleIndicies[i] = i;
      }

      //Indicies of the quad
      GLushort QuadIndices[] =
      {
        0, 1, 2,
        0, 2, 3
      };

      //Generate the buffers
      glGenVertexArrays(1, &_quadInfo.vao);
      glGenBuffers(1, &_quadInfo.vbo);
      glGenBuffers(1, &_quadInfo.ebo);

      //Bind the vertex array object to remember the data
      //Remember OpenGL is like a state machine, one thing at a time
      glBindVertexArray(_quadInfo.vao);

      //Bind the buffer for the quad
      glBindBuffer(GL_ARRAY_BUFFER, _quadInfo.vao);
      //Allocate memory on the GPU from the quad from above
      glBufferData(GL_ARRAY_BUFFER, //Type of Buffer saving to
        sizeof(GraphicsQuad),  //Size of the data
        GraphicsQuad,          //Where the data stats
        GL_STATIC_DRAW);      //Data store contents will be modified once and used many times.

      //Bind the buffer for the elements/indicies for the quad
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadInfo.ebo);
      //Same exact thing as the vao but this time with the indicies
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QuadIndices), QuadIndices, GL_STATIC_DRAW);

      //Telling OpenGL how to read the data
      glEnableVertexAttribArray(0);//for vert, in the shader location=0
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
      glEnableVertexAttribArray(1);//for UV, in the shader location=1
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
        (void*)(sizeof(GLfloat) * 3));

      //Binding to 0 will unbind the buffers so you cannot modify the data
      glBindVertexArray(0); //_quadInfo.vao will now remember how to read your Data from GraphicsQuad
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      ////////////////////////////////////////////////////////////////
      //FOR CIRCLES
      glGenVertexArrays(1, &_circleInfo.vao);
      glGenBuffers(1, &_circleInfo.vbo);
      glGenBuffers(1, &_circleInfo.ebo);

      glBindVertexArray(_circleInfo.vao);
      glBindBuffer(GL_ARRAY_BUFFER, _circleInfo.vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _circleInfo.ebo);

      glBufferData(GL_ARRAY_BUFFER, sizeof(circleMesh), circleMesh, GL_STATIC_DRAW);
     
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _circleInfo.ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circleIndicies), circleIndicies, GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);//for vert, in the shader location=0

        //Telling opengl how to read your data
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
      
      glBindVertexArray(0); 
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }

    void GLGraphics::DeleteMesh()
    {
      //Clean up after yourself when allocating memory
      if (_quadInfo.vao < 0)
      {
        glDeleteBuffers(1, &_quadInfo.vao);
      }
      if (_quadInfo.ebo < 0)
      {
        glDeleteBuffers(1, &_quadInfo.ebo);
      }
      if (_quadInfo.vbo < 0)
      {
        glDeleteBuffers(1, &_quadInfo.vbo);
      }


      //DELETE CIRCLE
      if (_circleInfo.vao < 0)
      {
        glDeleteBuffers(1, &_quadInfo.vao);
      }
      if (_circleInfo.ebo < 0)
      {
        glDeleteBuffers(1, &_quadInfo.ebo);
      }
      if (_circleInfo.vbo < 0)
      {
        glDeleteBuffers(1, &_quadInfo.vbo);
      }

    }//DeleteMesh

  } // Systems
} //AlJeEngine