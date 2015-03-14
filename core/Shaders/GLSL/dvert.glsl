/**************************************************************************************/
/*!
@file dvert.glsl
@author Jeffrey Uong
*/
/**************************************************************************************/

#version 330 core
layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;



void main() 
{
   mat4 mymodel = mat4(
   vec4(.5,0,0,0),
   vec4(0,.5,0,0),
   vec4(0,0,.5,0),
   vec4(0,0,0,1)
   ) ;
   gl_Position =  model * vec4(position.x, position.y, position.z , 1.0);
}