/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#ifndef GLSHADER_H
#define GLSHADER_H

#include "../../../../dependencies/include/GL/glew.h"
#include "GLShaderUniforms.h"
#include <string> //string
#include <iostream> //cout, endl
#include <vector> //std::vector
#include <unordered_map>//std::unordered_map
#include <memory> // std::shared_ptr

namespace AlJeEngine
{
  const int maxShaderType = 3;
  class GLShader
  {
  public:
    enum ShaderType {VERTEX = 0, FRAGMENT ,GEOMETRY};
  
    GLShader();  //ctor
    ~GLShader(); //dtor

    template<typename T>
    void UpdateUniforms(const std::string &uniformName, const T &data);
    void FindUniforms(const std::string &uniformName);
    void LoadShaderFile(const char *vert, const char *frag, const char *geo);
    void Compile(); //Compile the shader itself
    void Use();   //Use the shader
    void UnUse(); //Don't use the shader
  private:
      
    bool CompileFile(ShaderType type); //Compiles shaders files
    bool _shaderflags[maxShaderType];  //to check which shaders compiled
    GLuint _shaderProgram;
    GLuint _shaderID[maxShaderType];
    std::string _shaderFile[maxShaderType];
    std::unordered_map<std::string, GLint> _shaderUniforms;
  };

  typedef std::shared_ptr<GLShader> ShaderPtr;

  template<typename T>
  void GLShader::UpdateUniforms(const std::string &uniformName, const T &data) 
  {
    //Using a standard unordered map to hold all my data.
    //The string will be used as a key to find my data in the map
    //Read more at http://en.cppreference.com/w/cpp/container/unordered_map
    LoadShaderData(_shaderUniforms[uniformName], data);
  }
  
}

#endif