
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <memory>
#include "../../engine/headers/Gamestate.h"
#include "../../engine/headers/System.h"
#include "../../components/ComponentsInclude.h"
namespace AlJeEngine
{
  namespace Gamestates
  {

    class MainMenu : public Gamestate
    {
    public:
      MainMenu() : Gamestate("Main Menu Gamestate", GS_MainMenu)
      {
        /* the engine calls init manually,
        which should typically take the place of most of the constructor. */
      }

      ~MainMenu() {}
      void Init();

      void Update(float);

      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:

      void createButtons();

    };

    typedef std::shared_ptr<MainMenu> MainMenuPtr;

  }; // Systems

}; // AlJeEngine

