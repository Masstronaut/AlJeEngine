/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#ifndef GLGRAPHICS_H
#define GLGRAPHICS_H

#include "../../../engine/headers/System.h"
#include <GL/glew.h> //Lots of opengl functions
#include <unordered_map> //unordered_map
#include "GLShader.h"


namespace AlJeEngine
{
  namespace Systems
  {
    class GLGraphics : public System
    {
    public:
      enum MeshType { QUAD = 0, CIRCLE };

      GLGraphics(); //ctor
      void Init(void);       //Initilize SDL
      void Update(float dt); //Update everyframe  
      void Shutdown(void);   //called when system is deleated

      void newFrame();

    private:
      struct MeshInfo
      {
        GLuint vbo;//vertex buffer object
        GLuint vao;//vertex array object
        GLuint ebo;//element array object

        MeshInfo() :vbo(0), vao(0), ebo(0) {}//Init everything to 0
      };

      void DrawEntity(const EntityPtr&, const CameraPtr&);
      void CreateMesh();
      void DeleteMesh();
      MeshInfo _quadInfo;
      
      ShaderPtr getShader(std::string);
      void addShader(std::string, ShaderPtr);

      typedef std::unordered_map<std::string, ShaderPtr> ShaderMap;

      ShaderMap _shaders;


    };

    typedef std::shared_ptr<GLGraphics> GLGraphicsPtr;

  } // Systems

} // AlJeEngine


#endif
