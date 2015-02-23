/**************************************************************************************/
/*!
@file dfrag.glsl
@author Jeffrey Uong
@copyright All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/**************************************************************************************/

#version 330 core

in vec2 Texcoord;

uniform vec4 color;

void main()
{
  vec4 textureColor = texture(tex, Texcoord) * spriteColor;
  gl_FragColor = textureColor;
}