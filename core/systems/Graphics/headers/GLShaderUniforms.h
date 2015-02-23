/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#ifndef GLSHADERUNIFORMS_H
#define GLSHADERUNIFORMS_H
#include "GLShader.h"
#include "../../../dependencies/include/GL/glew.h"
#include "../../../lib/math/glm/glm.hpp" //vec2,vec3,vec4, matri4x4
#include "../../../lib/math/glm//gtc/type_ptr.hpp" //value_ptr


void LoadShaderData(const GLint location, const GLint &data);
//void LoadShaderData(const GLint location, const GLuint &data);
void LoadShaderData(const GLint location, const  GLfloat &data);
void LoadShaderData(const GLint location, const glm::vec2 &data);
void LoadShaderData(const GLint location, const glm::vec3 &data);
void LoadShaderData(const GLint location, const glm::vec4 &data);
void LoadShaderData(const GLint location, const glm::mat3x3 &data);
void LoadShaderData(const GLint location, const glm::mat4x4 &data);



#endif