/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#ifndef GLSHADER_H
#define GLSHADER_H

#include <string> //string
#include "../../../dependencies/include/GL/glew.h"
#include <vector> //std::vector
#include <unordered_map>//unordered_map
namespace AlJeEngine
{
  const int maxShaderType = 3;
  class GLShader
  {
  public:
    enum ShaderType {VERTEX = 0, FRAGMENT ,GEOMETRY};
      //ctor
    GLShader();
    ~GLShader(); //dtor

    void AddUniforms(std::string uniformName);
    void LoadShaderFile(std::string vert, std::string frag, std::string geo);
    void Compile(); //Compile the shader itself
    void Use();   //Use the shader
    void UnUse(); //Don't use the shader
  private:
      
    bool CompileFile(ShaderType type); //Compiles shaders files
    bool _shaderflags[maxShaderType];  //to check which shaders compiled
    template<typename T> void Uniformdata(T dataType);
    GLuint _shaderProgram;
    GLuint _shaderID[maxShaderType];
    std::string _shaderFile[maxShaderType];
    std::unordered_map<std::string, GLuint> _shaderUniforms;
  };

}

#endif