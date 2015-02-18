

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "../components/Components.h"
#include "headers/Engine.h"
#include <memory>

using namespace AlJeEngine;

int main( )
{
  std::shared_ptr < Engine > ENGINE( new Engine( ) );
  ENGINE->Init( );
  ENGINE->mainLoop( );

  return 0;
}
