/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../engine/headers/Component.h"
#include <memory>

namespace AlJeEngine
{
  class Score : public Component
  {
  public:
    Score() : Component(EC_Score, MC_Score)
                  {
                  }

    float score = 0.f;
  };

  typedef std::shared_ptr<Score> ScorePtr;

}; // namespace AlJe