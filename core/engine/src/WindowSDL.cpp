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

    void WindowSDL::PollWindowEvent(void)
    {
      if (SDL_PollEvent(&_event))
      {
        switch (_event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
          std::cout << "Window closed" << std::endl;
          break;
        case SDL_WINDOWEVENT_MOVED:
          std::cout << "Window moved" << std::endl;
          break;
        case SDL_WINDOWEVENT_RESIZED:
          std::cout << "Window Resized" << std::endl;
          SDL_GetWindowSize(_window, &_width, &_height);
          break;
        case SDL_QUIT:
          ENGINE->Stop();
          break;
        default:
          //throw std::invalid_argument("Event from WindowSDL Unknown");
          break;
        }//switch

      }//event

        //Swap the back buffer and front buffer
      SDL_GL_SwapWindow(_window);
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
      PollWindowEvent();
    }


  } // Systems
} // AlJeEngine
