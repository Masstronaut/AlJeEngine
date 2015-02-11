

#include "headers/Engine.h"
#include <memory>
int main( )
{
  std::shared_ptr < Engine > ENGINE( new Engine( ) );
  ENGINE->Init( );
  ENGINE->mainLoop( );

  return 0;
}
