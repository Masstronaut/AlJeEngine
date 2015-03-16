

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include <GL/glew.h>
#include <iostream>
#include "../components/Components.h"
#include <SDL_opengl.h>
#include <SDL.h>
#include "headers/Engine.h"
#include <memory>
#include <fstream>

using namespace AlJeEngine;

namespace AlJeEngine
{
  extern Engine* ENGINE;
}

int main(int argc, char* args[])
{

  // Create the Engine.
  ENGINE = new Engine( );

  ENGINE->Init( );
  ENGINE->mainLoop( );

  // Shutdown the engine when it's no longer running
  ENGINE->Shutdown();

  // Don't leak memory!
  delete ENGINE;

  return 0;
}
