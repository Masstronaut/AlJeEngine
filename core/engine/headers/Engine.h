
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

    void Update(float dt);

    void mainLoop();

    float FrameTime();

    Space& CreateSpace(std::string &name);

    Space& GetSpace(std::string &name);

    Space& SetActiveSpace(std::string &name);
    Space& GetActiveSpace();

  private:
    float dt;

    std::string _activeSpace;

    std::unordered_map<std::string, Space> _spaces;

    SystemVec _systems;

    bool _running = true;
  };

}; // AlJeEngine
