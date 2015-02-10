
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 * @brief The Engine class is the core of the game engine.
 * 
 */


#pragma once
#include <memory> // Shared pointers for automatic memory management

struct Engine
{

  void Init();
  void Shutdown();

  void Update(float);

  void mainLoop();

private:
  void populateEntities(shared_ptr < System > sys);
  std::vector < shared_ptr < System > > _systems;
  std::vector < shared_ptr < Entity > > _entities;

  bool _running;
};

