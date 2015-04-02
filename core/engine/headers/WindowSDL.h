#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <memory>
#include <GL/glew.h> //glewInit()
#include <SDL.h>
#include <SDL_opengl.h>
#include "../../engine/headers/System.h"
#include "../glm/vec2.hpp"
#include <utility> //std::pair


namespace AlJeEngine
{
  namespace Systems
  {

    class WindowSDL : public System
    {
    public:
      WindowSDL();  //ctor
      void Init(void);   //Initialize SDL
      void Update(float dt); //Update every frame  
      void Shutdown(void); //called when system is deleted
      bool GetMouseTrigger(void);
      bool GetMouseReleased();
      void ToggleFullScreen();
      glm::vec2 GetMousePosition(void);
      int GetWindowHeight(void);
      int GetWindowWidth(void);
      std::pair<int, int> GetWindowDimensions(void);
      void SendMsg(EntityPtr, EntityPtr, Message::Message);
    private:
      struct SDLMouse
      {
        glm::vec2 position;
        bool Pressed;
        bool Released;
        bool Trigger;
      };

      void PollEvents(void);
      void PollWindowEvent(SDL_Event &currentEvent);
      void PollKeyEvent(SDL_Event &currentEvent);
      void PollMouseEvent(SDL_Event &currentEvent);

      SDL_Window* _window;    //The actual window data
      SDL_GLContext _context; //OpenGL context
      SDL_Event _event; //Events from the window
      bool _fullScreen; // if the screen is fullscreen or not 
      int _width;         //Window width
      int _height;        //Window height
      SDLMouse _theMouse;
    };

    typedef std::shared_ptr<WindowSDL> WindowSDLPtr;

  } // Systems
} // AlJeEngine
#endif
