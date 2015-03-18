

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include "../engine/headers/Component.h"
#include "../../lib/math/glm/glm.hpp"
#include <memory>

namespace AlJeEngine
{
  class Particle : public Component
  {
  public:
    Particle() : Component(EC_Particle, MC_Particle)
                  {
                  }

    enum EffectType { Fire, Fade };
    // This might get implemented later
    //EffectType effect;
    float lifetime = 2.f;
    glm::vec2 velocity = { 0.0f, 0.0f };
  };

  typedef std::shared_ptr<Particle> ParticlePtr;

}; // namespace AlJe