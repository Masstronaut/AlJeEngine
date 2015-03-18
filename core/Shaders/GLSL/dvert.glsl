/**************************************************************************************/
/*!
@file dvert.glsl
@author Jeffrey Uong
@copyright All content © 2015 Allan Deutsch & Jeff Uong. All rights reserved.
*/
/**************************************************************************************/

#version 330 core
layout(location = 0)in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() 
{
   gl_Position = proj * view * model * vec4(position.x, position.y, 0, 1.0);
}