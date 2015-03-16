/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/WindowSDL.h"
#include "../headers/Engine.h"
#include <iostream> //cout, endl

const int screenWidth = 1280;
const int screenHeight = 720;

namespace AlJeEngine
{
  extern Engine* ENGINE;
  namespace Systems
  {

    WindowSDL::WindowSDL() : System(std::string("WindowSDLSystem"), ES_WindowSDL)
    {

      _window = nullptr;
      _context = NULL;
      _width = screenWidth;
      _height = screenHeight;
    }

    void WindowSDL::Init()
    {
      SDL_Init(SDL_INIT_VIDEO);

      //Telling OpenGL to be compatible as version 4.0
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

      //Creating the screen and setting position and screen size
      _window = SDL_CreateWindow("AlJeEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        _width, _height, SDL_WINDOW_OPENGL);

      //Creating the context for OpenGL
      _context = SDL_GL_CreateContext(_window);

      //Force GLEW to use modern OpenGL methods if available
      glewExperimental = GL_TRUE;
      glewInit();
    }

    void WindowSDL::Shutdown(void)
    {
      //Delete the context
      SDL_GL_DeleteContext(_context);
    }

    bool WindowSDL::GetMouseTrigger(void)
    {
      return _theMouse.Trigger;
    }

    std::pair<int, int> WindowSDL::GetMousePosition(void)
    {
      return std::pair<int,int>(_theMouse.position.first, _theMouse.position.second);
    }

    void WindowSDL::PollWindowEvent(SDL_Event &currentEvent)
    {
      switch (currentEvent.type)
      {
      case SDL_WINDOWEVENT:
        switch (currentEvent.window.event)
        {
        case SDL_WINDOWEVENT_CLOSE:
          break;
        case SDL_WINDOWEVENT_MOVED:
          break;
        case SDL_WINDOWEVENT_RESIZED:
          SDL_GetWindowSize(_window, &_width, &_height);
          break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
          break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
          break;
        }
        break;
      case SDL_QUIT:
        ENGINE->Stop();
        break;
      default:
        break;
      }//switch
    }

    void WindowSDL::PollKeyEvent(SDL_Event &currentEvent)
    {
      switch (currentEvent.type)
      {
      case SDL_KEYDOWN:
        //If the key that is down is the escape key
        if (currentEvent.key.keysym.sym == SDLK_ESCAPE)
        {
          //Exit the game
          ENGINE->Stop();
        }
        break;
      case SDL_KEYUP:
        break;
      }

    }

    void WindowSDL::PollMouseEvent(SDL_Event &currentEvent)
    {
      switch (currentEvent.type)
      {
      case SDL_MOUSEMOTION:
        _theMouse.position.first  = _event.motion.x;
        _theMouse.position.second = _event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (currentEvent.button.button == SDL_BUTTON_LEFT)
        {
          if (_theMouse.Pressed == false)
            _theMouse.Trigger = true;
          else
            _theMouse.Trigger = false;

          _theMouse.Released = false;
          _theMouse.Pressed = true;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if (currentEvent.button.button == SDL_BUTTON_LEFT)
        {
          _theMouse.Pressed = false;
          _theMouse.Released = true;

        }
        
        break;
      default:
        break;
      }
    }

    void WindowSDL::PollEvents(void)
    {
      if(SDL_PollEvent(&_event))
      {
        PollWindowEvent(_event);
        PollKeyEvent(_event);
        PollMouseEvent(_event);
      }
    }

    int WindowSDL::GetWindowHeight(void)
    {
      return _height;
    }

    int WindowSDL::GetWindowWidth(void)
    {
      return _width;
    }

    std::pair<int, int> WindowSDL::GetWindowDimensions(void)
    {
      std::pair<int, int> dimensions(_width, _height);
      SDL_GetWindowSize(_window, &dimensions.first, &dimensions.second);
      return dimensions;
    }

    void WindowSDL::Update(float dt)
    {
      PollEvents();
        //Swap the back buffer and front buffer
      SDL_GL_SwapWindow(_window);
    }


  } // Systems
} // AlJeEngine
