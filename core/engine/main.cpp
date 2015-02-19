

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../components/Components.h"
#include <GL/glew.h>
#include "headers/Engine.h"
#include <SDL_opengl.h>
#include "../../dependencies/include/SDL.h"
#include <memory>


using namespace AlJeEngine;

int main(int argc, char* args[])
{
  std::shared_ptr < Engine > ENGINE( new Engine( ) );
  ENGINE->Init( );
  ENGINE->mainLoop( );

  return 0;
}
