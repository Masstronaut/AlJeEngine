
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <memory>
#include "../../engine/headers/Engine.h"
#include "../../engine/headers/System.h"
#include "../../components/ComponentsInclude.h"
#include "../SystemsInclude.h"

namespace AlJeEngine
{
  namespace Systems
  {

    class Movement : public System
    {
    public:
      Movement() : System(std::string("Movement System"), ES_Movement) {/* the engine calls init manually, which should take the place of most of the constructor. */ }

      void Init();

      void Update(float);

      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:
      void ApplyThrust(EntityPtr, float thrust);
      void ApplyRotation(EntityPtr, float rotationSpeed);

    };

    typedef std::shared_ptr<Movement> MovementPtr;

  }; // Systems

}; // AlJeEngine

