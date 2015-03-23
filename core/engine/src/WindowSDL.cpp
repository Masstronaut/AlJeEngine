/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/WindowSDL.h"
#include "../headers/Engine.h"
#include <iostream> //cout, endl
#include "../glm/gtc/matrix_transform.hpp"

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
      RegisterComponent(MC_NOOBJECTS);

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

    glm::vec2 WindowSDL::GetMousePosition(void)
    {
      return _theMouse.position;
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
      {
        //1 maps to near plane, -1 far plane
        std::pair<int, int> windowDimensions;
        windowDimensions = GetWindowDimensions();
        CameraPtr camera = ENGINE->GetActiveSpace()->GetCamera()->GET_COMPONENT(Camera);
        glm::vec3 mousescreen(_event.motion.x, _event.motion.y, 1);
        glm::mat4 invert;
        invert[0][0] = 1;
        invert[1][1] = -1;
        invert[2][2] = 1;
        invert[3][3] = 1;
        glm::vec4 viewport(0, 0, windowDimensions.first, windowDimensions.second);
        glm::vec3 mousepoint = glm::unProject(mousescreen, invert * camera->_viewMatrix, camera->_ortho, viewport);
        _theMouse.position.x = mousepoint.x / 10.f;
        _theMouse.position.y = mousepoint.y / 10.f;
        std::cout << "Mouse X: " << _theMouse.position.x << std::endl;
        std::cout << "Mouse Y: " << _theMouse.position.y << std::endl;
      }
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
      CameraPtr camera = ENGINE->GetActiveSpace()->GetCamera()->GET_COMPONENT(Camera);
      glm::vec2 mousepos= GetMousePosition();
      PollEvents();
      //glm::unProject(glm::vec3(mousepos.x, mousepos.y, 0), camera->_viewMatrix,camera->_pespective,


      //Swap the back buffer and front buffer
      // This effectively begins the next frame.
      SDL_GL_SwapWindow(_window);
    }


  } // Systems
} // AlJeEngine
