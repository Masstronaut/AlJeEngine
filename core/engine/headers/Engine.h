
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
#include <unordered_map>
#include "System.h"
#include "Entity.h"
#include "Space.h"

namespace AlJeEngine
{

  struct Engine
  {

    void Init();

    void Shutdown();

    void Update(float);

    void mainLoop();

    // <chrono> automated scoped-based timer would be awesome, please do that future Allan.
#pragma message ("Add frame time stuff to engine")
    float FrameTime();
#pragma message ("Add a way to access spaces")

  private:
    float dt;

    std::unordered_map<std::string, Space> _spaces;

    SystemVec _systems;

    bool _running = true;
  };

}; // AlJeEngine
