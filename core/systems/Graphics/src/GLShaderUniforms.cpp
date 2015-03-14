/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../headers/GLShaderUniforms.h"
#include "../../../lib/math/glm//gtc/type_ptr.hpp" //value_ptr

void LoadShaderData(const GLint location, const GLint &data)
{
  glUniform1i(location, data);
}

void LoadShaderData(const GLint location, const GLuint &data)
{
  glUniform1ui(location, data);
}

void LoadShaderData(const GLint location, const GLfloat &data)
{
  glUniform1f(location, data);
}

void LoadShaderData(const GLint location, const glm::vec2 &data)
{
    //glm::value_ptr helps data transfer over to the GPU
    //in other words converts it into a pointer
  glUniform2fv(location, 1, glm::value_ptr(data));
}

void LoadShaderData(const GLint location, const glm::vec3 &data)
{
    //glm::value_ptr helps data transfer over to the GPU
    //in other words converts it into a pointer
  glUniform3fv(location, 1, glm::value_ptr(data));
}

void LoadShaderData(const GLint location, const glm::vec4 &data)
{
    //glm::value_ptr helps data transfer over to the GPU
    //in other words converts it into a pointer
  glUniform4fv(location, 1, glm::value_ptr(data));
}

void LoadShaderData(const GLint location, const glm::mat3x3 &data)
{
    //glm::value_ptr helps data transfer over to the GPU
    //in other words converts it into a pointer
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
}

void LoadShaderData(const GLint location, const glm::mat4x4 &data)
{
    //glm::value_ptr helps data transfer over to the GPU
    //in other words converts it into a pointer
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
}