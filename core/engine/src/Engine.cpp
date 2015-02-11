
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 *
 * @brief The Engine class is the core of the game engine.
 *
 */

#include "../headers/Engine.h"
#include <iostream>
using std::cout;
void Engine::Init()
{
  _running = true;
  // Add systems here



  // initialize all systems
  // using c++11 range-based for loop
  for(auto sys : _systems)
    sys->Init();

}

void Engine::Shutdown( )
{
  for(auto sys : _systems)
    sys->Shutdown( );

}

void Engine::Update( float dt )
{
  for( auto sys : _systems )
  {
    // Make sure the system has all the entities that meet it's requirements
    populateEntities( sys );

    sys->Update( dt );
  }
  cout << "updated: "<< dt << "ms\n";

}

void Engine::mainLoop()
{
  while( _running )
  {
    // some frametime logic
    // probably dependent on the graphics library

    float dt = 0.016667f;
    // Update all the systems
    Update( dt );
  }
}

void Engine::populateEntities( std::shared_ptr < System > sys )
{
  sys->_entities.clear( );
  for( auto it : _entities)
    if( ( it->Mask( ) & sys->Mask( ) ) == sys->Mask( ) )
      sys->_entities.push_back( it );
}
