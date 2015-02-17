
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
#include <vector>
#include "System.h"
#include "Entity.h"

namespace AlJeEngine
{

  struct Engine
  {

    void Init();
    void Shutdown();

    void Update(float);

    void mainLoop();

#pragma message ("Add frame time stuff to engine")

  private:
    void populateEntities(std::shared_ptr < System > sys);
    std::vector < std::shared_ptr < System > > _systems;
    std::vector < std::shared_ptr < Entity > > _entities;

    bool _running;
  };

}; // AlJeEngine
