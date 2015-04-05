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

    class BulletController : public System
    {
    public:
      BulletController() : System(std::string("Bullet Controller System"), ES_BulletController) {/* the engine calls init manually, which should take the place of most of the constructor. */ }

      void Init();

      void Update(float);

      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:

      void resolveBulletHit(EntityPtr, EntityPtr);

    };

    typedef std::shared_ptr<BulletController> BulletControllerPtr;

  }; // Systems

}; // AlJeEngine

