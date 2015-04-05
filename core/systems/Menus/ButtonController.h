
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
#include "../../components/Components.h"
#include "../SystemsInclude.h"

namespace AlJeEngine
{
  namespace Systems
  {

    class ButtonController : public System
    {
    public:
      ButtonController() : System(std::string("Button Controller System"), ES_ButtonController) {/* the engine calls init manually, which should take the place of most of the constructor. */ }

      void Init();

      void Update(float);

      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:
      void CheckButtonControllers();

    };

    typedef std::shared_ptr<ButtonController> ButtonControllerPtr;

  }; // Systems

}; // AlJeEngine

