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
  namespace MenuAction
  {
    enum MenuAction
    {
      // main menu actions:
      MM_Exit,
      MM_Start,
      MM_Credits,
      MM_HowToPlay,
      MM_Settings,

      // Pause menu actions:
      PM_Resume,
      PM_Quit,
      PM_Restart,
      PM_Options
    };
  }

  class MenuObject : public Component
  {
  public:
    MenuObject() : Component(EC_MenuObject, MC_MenuObject)
                  {
                  }
    
    enum MenuType { PAUSE, MAIN };

    MenuType _menuType;

    MenuAction::MenuAction _action;


  };

  typedef std::shared_ptr<MenuObject> MenuObjectPtr;

}; // namespace AlJe