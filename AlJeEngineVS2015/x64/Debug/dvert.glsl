/**************************************************************************************/
/*!
@file dvert.glsl
@author Jeffrey Uong
@copyright All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/**************************************************************************************/

#version 330 core
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;

out vec2 Texcoord;

uniform mat4 model;

void main() 
{
   gl_Position = model * vec4(position, 1.0);
   Texcoord = texcoord;
}