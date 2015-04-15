#include "../headers/GLShader.h"
#include <iostream>//cout, endl
#include <fstream> //ifstream

namespace AlJeEngine
{
  
  /*!
  * @brief Gets the mouse trigger during the pressed frame.
  * @param filename the name of the file in the GLSL folder
  * @param storage the string the whole shader will be stored in
  * @return bool if shader could of been read from a file or not
  */
  bool ShaderReader(const char *filename, std::string &storage)
  {
    storage.clear(); //Clear it to make sure it's empty
    if (filename == nullptr)
    {
      return false;
    }

    std::string file(filename);
    //hardcoding the location to be in the GLSL folder
    std::string location ("../../core/Shaders/GLSL/"); 
    location += file;

    std::ifstream shaderfile(location.c_str(), std::ios::in);
    if (shaderfile)
    {
      storage.assign((std::istreambuf_iterator<char>(shaderfile)),
        std::istreambuf_iterator<char>());
    }
    else
    {
      std::cout << "Could not open file " << filename << std::endl;
      return false;
    }
    shaderfile.close();
    return true;
  }

  /*!
  * @brief Checks if the shader was able to compile.
  * @param shaderID the shader handle that openGL gives you when making a shader
  * @return bool if the shader had an error it will print it out
  */
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
      printf("Loading Shader Error. %s\n", buffer); //You can print this or throw
      delete[] buffer; //Watching out for memory leaks
      return GL_FALSE; //Abort, mission failed
    }
    return GL_TRUE;
  }

  /*!
  * @brief Checks if the shader program is able to link properly.
  * @param ProgramID the shader program handle that openGL gives you when making a shader
  * @return bool if the shader program is able to link properly 
  */
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

  /*!
  * @brief Compiles the shader type accociated with the file
  * @param type the type of shader it is
  * @return bool if the shader is able to compile
  */
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

  /*!
  * @brief Ctor for the shader, making sure the shader's value is init
  */
  GLShader::GLShader()
  {
    for(int i = 0; i < maxShaderType; ++i)
    {
      _shaderID[i] = 0;
      _shaderFile[i].clear();
      _shaderflags[i] = false;
    }  
    _shaderProgram = 0;
  }

  /*!
  * @brief dtor for the shader class, delete the handle of the shader
  */
  GLShader::~GLShader()
  {
    for (int i = 0; i < maxShaderType; ++i)
    {
      glDeleteShader(_shaderID[i]);
      _shaderFile[i].clear();
    }
    
  }

  /*!
  * @brief Loads the vert, frag, and/or the geometry shader
  * @param vert the vert shader in char to be loaded
  * @param frag the frag shader in char to be loaded
  * @param geo the geometry shader in char to be loaded
  */
  void GLShader::LoadShaderFile(const char *vert,
    const char *frag, const char *geo)
  {
    _shaderflags[VERTEX]   = ShaderReader(vert, _shaderFile[VERTEX]);
    _shaderflags[FRAGMENT] = ShaderReader(frag, _shaderFile[FRAGMENT]);
    _shaderflags[GEOMETRY] = ShaderReader(geo, _shaderFile[GEOMETRY]);
    bool bvert = _shaderflags[VERTEX];
    bool bfrag = _shaderflags[FRAGMENT];
    bool bgeo  = _shaderflags[GEOMETRY];
  }

  /*!
  * @brief finds the uniform data in the current shader
  * @param uniformName the name of the uniform the user wants to find
  */
  void GLShader::FindUniforms(const std::string &uniformName)
  {
      //Finding the uniform in the shader.
      //glGetUniformLocation should only be called once since it is pointless to call
      //this function multiple times.
    _shaderUniforms[uniformName] = glGetUniformLocation(_shaderProgram, uniformName.c_str());
    if (_shaderUniforms[uniformName] == -1)
    {
      std::cout << uniformName << " could not be found in the shader" << std::endl;
    }
  }

  /*!
  * @brief Compiles the shader in order to be usable
  */
  void GLShader::Compile()
  {
      //Shaders need both a vertex and a fragment to be whole
    if (_shaderflags[VERTEX] == false && _shaderflags[FRAGMENT] == false)
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

  /*!
  * @brief Binds the shader to be ready to use for the current draw
  */
  void AlJeEngine::GLShader::Use()
  {
      //Use the current shader;
    glUseProgram(_shaderProgram);
  }

  /*!
  * @brief UnBinds the shader to stop using the shader
  */
  void AlJeEngine::GLShader::UnUse()
  {
      //Unbinding the current shader
    glUseProgram(0);
  }


}//AljeEngine
