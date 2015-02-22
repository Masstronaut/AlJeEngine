#include "../headers/GLShader.h"
#include <iostream>//cout, endl
#include <fstream> //ifstream



namespace AlJeEngine
{
  
  static bool ShaderReader(const char *filename, std::string &storage)
  {
    storage.clear();
    std::string location = "../../Shaders/GLSL/";
    location += filename;
    std::ifstream shaderfile(location.c_str(), std::ios::in);
    if (shaderfile)
    {
      storage.assign((std::istreambuf_iterator<char>(shaderfile)),
        std::istreambuf_iterator<char>());
    }
    else if (storage.length() == 0)
      return false;
    else
    {
      std::cout << "Could not open file " << filename << std::endl;
      return false;
    }
    shaderfile.close();
    return true;
  }

  static GLboolean checkShaderStatus(GLuint shaderID)
  {
    GLint shaderStatus;
      //Check for error for shaders, returns TRUE if success
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderStatus);
    //Print error if we get an error from shader
    if (shaderStatus != GL_TRUE)
    {
      GLint shaderInfoLogLen;
      //getting the # of char in the log
      glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &shaderInfoLogLen);
      GLchar *buffer = new GLchar[shaderInfoLogLen]; //allocate memory b/c size unkn
      glGetShaderInfoLog(shaderID, shaderInfoLogLen, NULL, buffer);
      printf("Loading Shader Error. %s\n", buffer);
      delete[] buffer; //Watching out for memory leaks
      return GL_FALSE; //Abort, mission failed
    }
    return GL_TRUE;
  }

  static GLboolean checkProgramStatus(GLuint ProgramID)
  {
    GLint linkStatus;
      //Check for error for shaders, returns TRUE if success
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &linkStatus);
      //Print error if we get an error from shader
    if (linkStatus != GL_TRUE)
    {
      GLint shaderInfoLogLen;
        //getting the # of char in the log
      glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &shaderInfoLogLen);
      char *buffer = new char[shaderInfoLogLen]; //allocate memory b/c size unknown
      glGetProgramInfoLog(ProgramID, shaderInfoLogLen, nullptr, buffer);
      printf("Linking Shader Error. %s\n", buffer);
      delete[] buffer; //Watching out for memory leaks
      return GL_FALSE; //Abort, mission failed
    }
    return GL_TRUE;
  }

  bool GLShader::CompileFile(ShaderType type)
  {
    const char *file = _shaderFile[type].c_str();
    switch (type)
    {
    case VERTEX:
      
      _shaderID[type] = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(_shaderID[type], 1, &file, NULL);
      glCompileShader(_shaderID[type]);
      break;
    case FRAGMENT:
      _shaderID[type] = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(_shaderID[type], 1, &file, NULL);
      glCompileShader(_shaderID[type]);
      break;
    case GEOMETRY:
      _shaderID[type] = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(_shaderID[type], 1, &file, NULL);
      glCompileShader(_shaderID[type]);
      break;
    default:
      std::cout << "Put your own error message here" << std::endl;
      break;
    }
    if (!checkShaderStatus(_shaderID[type]))
    {
      return false;
    }
    return true;
  }

  GLShader::GLShader()
  {
    for(int i = 0; i < maxShaderType; ++i)
    {
      _shaderID[i] = 0;
      _shaderFile[i].clear();
    }  
    _shaderProgram = 0;
  }

  GLShader::~GLShader()
  {
    for (int i = 0; i < maxShaderType; ++i)
    {
      glDeleteShader(_shaderID[i]);
      _shaderFile[i].clear();
    }
    
  }

  void GLShader::AddUniforms(std::string uniformName)
  {
    glGetUniformLocation(_shaderUniforms[uniformName], uniformName.c_str());
    if (_shaderUniforms[uniformName] == -1)
    {
      std::cout << uniformName << " could not be found" << std::endl;
    }
  }

    void GLShader::LoadShaderFile(std::string vert, std::string frag, std::string geo = 0)
  {
    _shaderflags[VERTEX]   = ShaderReader(vert.c_str(), _shaderFile[VERTEX]);
    _shaderflags[FRAGMENT] = ShaderReader(frag.c_str(), _shaderFile[FRAGMENT]);
    _shaderflags[GEOMETRY] = ShaderReader(frag.c_str(), _shaderFile[GEOMETRY]);
  }

  void GLShader::Compile()
  {
      //Shaders need both a vertex and a fragment to be whole
    if (!_shaderflags[VERTEX] && !_shaderflags[FRAGMENT])
    {
      std::cout << "Error, Vertex or Fragment shader is empty, cannot compile" << std::endl;
      return;
    }

    CompileFile(VERTEX);
    CompileFile(FRAGMENT);
      
      //Create a ID for the entire shader
    _shaderProgram = glCreateProgram();
    if (_shaderflags[GEOMETRY])
    {
      CompileFile(GEOMETRY);
  
        //Put all 3 of these files onto the program
      glAttachShader(_shaderProgram, _shaderID[VERTEX]);
      glAttachShader(_shaderProgram, _shaderID[FRAGMENT]);
      glAttachShader(_shaderProgram, _shaderID[GEOMETRY]);
        //Combine them together
      glLinkProgram(_shaderProgram);
        //Check the status of the shader
      checkProgramStatus(_shaderProgram);
    }
    else
    {   
        //Put 2 of the shaders onto the program
      glAttachShader(_shaderProgram, _shaderID[VERTEX]);
      glAttachShader(_shaderProgram, _shaderID[FRAGMENT]);
      glLinkProgram(_shaderProgram);
        //Check the status of the shader
      checkProgramStatus(_shaderProgram);
    }  
  }

  void AlJeEngine::GLShader::Use()
  {
    glUseProgram(_shaderProgram);
  }

  void AlJeEngine::GLShader::UnUse()
  {
    glUseProgram(0);
  }



}//AljeEngine
