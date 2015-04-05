
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../../systems/SystemsInclude.h"
#include "../GamestatesInclude.h"

namespace AlJeEngine
{
  extern Engine* ENGINE;

  using namespace Systems;
  namespace Gamestates
  {

      
    void PauseMenu::Init()
    {

      // Register for menu objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);
      RegisterComponent(MC_BoxCollider);
      RegisterComponent(MC_MenuObject);

      // Register the spaces that should be updated with this system.
      RegisterSpace("Pause Menu");

      // Set which space this gamestate's Update() function should be used with.
      SetLogicalSpace("Pause Menu");

      if (ENGINE->SpaceExists("Pause Menu"))
        return;
      // Create the pause menu space
      SpacePtr pauseMenu = ENGINE->CreateSpace("Pause Menu");


      pauseMenu->AddSystem(GETSYS(PhysicsDetect));
      pauseMenu->AddSystem(GETSYS(ButtonController));
      pauseMenu->AddSystem(GETSYS(CameraSystem));
      pauseMenu->AddSystem(GETSYS(GLGraphics));

      createButtons();

    }

    void PauseMenu::Update(float dt)
    {
     
    }

    void PauseMenu::Shutdown()
    {

    }

    void PauseMenu::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {
      switch (message)
      {
      case(Message::MV_MouseClick) :
        if (e1->CheckMask(MC_MenuObject))
        {
          // We don't care about pause menu items
          if (e1->GET_COMPONENT(MenuObject)->_menuType == MenuObject::MAIN)
            return;

          switch (e1->GET_COMPONENT(MenuObject)->_action)
          {
          case(MenuAction::PM_Resume) :
            ENGINE->PopGamestate();
            break;
          case(MenuAction::PM_Quit) :
            ENGINE->PopGamestate(); // pop the pause menu
            ENGINE->SendMsg(nullptr, nullptr, Message::MV_PopGamestate);
            //ENGINE->PopGamestate(); // pop the game gamestate
            break;
          case(MenuAction::PM_Restart) :

            break;
          case(MenuAction::PM_Options) :

            break;

          default:
            break;
          } // Menu Action
        }// Entity has a MenuObject Component
        break; // MouseClick message


      case(Message::MV_BackButton) :
        ENGINE->PopGamestate();
        break;

      default:
        break;
      }

    }

    void PauseMenu::createButtons()
    {
      // Get a pointer to the main menu space
      SpacePtr pauseMenu = ENGINE->GetSpace("Pause Menu");


      // Get the camera information
      TransformPtr cameraInfo = pauseMenu->GetCamera()->GET_COMPONENT(Transform);
      cameraInfo->scale = { cameraInfo->scale.x * .1f, cameraInfo->scale.y * .1f };
      glm::vec2 cameraPos = cameraInfo->position;
      glm::vec2 cameraSize = cameraInfo->scale;

      // Add a green start button
      EntityPtr start = ENGINE->Factory().create("Pause Menu Resume");
      start->GET_COMPONENT(Transform)->position = { cameraSize.x * .2f, cameraSize.y * .2f };

      // add the button to the space
      pauseMenu->AddEntity(start);

      // Add a red exit button
      EntityPtr exit = ENGINE->Factory().create("Pause Menu Quit");
      exit->GET_COMPONENT(Transform)->position = { -cameraSize.x * .2f, cameraSize.y * .2f };

      // add the button to the space
      pauseMenu->AddEntity(exit);

    }


  } // Gamestates

} // AlJeEngine