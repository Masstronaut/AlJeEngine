
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

    class PhysicsDetect : public System
    {
    public:
      PhysicsDetect() : System(std::string("Collision Detection System"), ES_PhysicsDetect) {/* the engine calls init manually, which should take the place of most of the constructor. */ }

      void Init();

      void Update(float);

      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

      bool AABBPointCheck(EntityPtr, glm::vec2);
      bool CirclePointCheck(EntityPtr, glm::vec2);
      bool AABBAABBCheck(EntityPtr, EntityPtr);
      bool AABBCircleCheck(EntityPtr, EntityPtr);
      bool CircleCircleCheck(EntityPtr, EntityPtr);
    private:
      void CheckMouseCollisions();

    };

    typedef std::shared_ptr<PhysicsDetect> PhysicsDetectPtr;

  }; // Systems

}; // AlJeEngine

