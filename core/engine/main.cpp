

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include <GL/glew.h>

#include "../components/Components.h"
#include <SDL_opengl.h>
#include <SDL.h>
#include "headers/Engine.h"
#include <memory>
#include <fstream>

using namespace AlJeEngine;

int main(int argc, char* args[])
{

  std::fstream testfile;
  testfile.open("testfile.txt", std::fstream::out);
  testfile << "This is a simple test";
  testfile.close();

  std::shared_ptr < Engine > ENGINE( new Engine( ) );
  ENGINE->Init( );
  ENGINE->mainLoop( );

  return 0;
}
