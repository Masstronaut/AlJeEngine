#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <GL/glew.h> //glewInit()
#include <SDL.h>
#include <SDL_opengl.h>
#include "../../engine/headers/System.h"

namespace AlJeEngine
{
  class WindowSDL : public System
  {
  public:
    WindowSDL();  //ctor
    void Init(void);   //Initilize SDL
    void Update(float dt); //Update everyframe
    void Shutdown(void); //called when system is deleated
    void PollWindowEvent(void);

  private:
    SDL_Window* _window;    //The actual window data
    SDL_GLContext _context; //OpenGL context
    SDL_Event _event; //Events from the window

  };
}
#endif
