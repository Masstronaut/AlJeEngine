
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

      
    void MainMenu::Init()
    {

      // Register the spaces that should be updated with this system.
      RegisterSpace("Main Menu");

      // Set which space this gamestate's Update() function should be used with.
      SetLogicalSpace("Main Menu");

      // Register for drawable objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);
      RegisterComponent(MC_BoxCollider);
      RegisterComponent(MC_MenuObject);


      if (ENGINE->SpaceExists("Main Menu"))
        return;

      // Create the main menu space
      SpacePtr mainMenu = ENGINE->CreateSpace("Main Menu");
      
      createButtons();

      mainMenu->AddSystem(GETSYS(PhysicsDetect));
      mainMenu->AddSystem(GETSYS(ButtonController));
      mainMenu->AddSystem(GETSYS(CameraSystem));
      mainMenu->AddSystem(GETSYS(GLGraphics));
    }

    void MainMenu::Update(float dt)
    {
     
    }

    void MainMenu::Shutdown()
    {

    }

    void MainMenu::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {
      switch (message)
      {
      case(Message::MV_MouseClick):
        if (e1->CheckMask(MC_MenuObject))
        {
          // We don't care about pause menu items
          if (e1->GET_COMPONENT(MenuObject)->_menuType == MenuObject::PAUSE)
            return;

          switch (e1->GET_COMPONENT(MenuObject)->_action)
          {
          case(MenuAction::MM_Start) :
            ENGINE->PushGamestate(TestPtr(new Test()));
            break;
          case(MenuAction::MM_Exit) :
            ENGINE->Stop();
            break;
          case(MenuAction::MM_Credits) :

            break;
          case(MenuAction::MM_HowToPlay) :

            break;
          case(MenuAction::MM_Settings) :

            break;

          default:
            break;
          } // Menu Action
        }// Entity has a MenuObject Component
        break; // MouseClick message



      case(Message::MV_BackButton) :
        ENGINE->Stop();
        break;

      default:
        break;
      }

    }

    void MainMenu::createButtons()
    {
      // Get a pointer to the main menu space
      SpacePtr mainMenu = ENGINE->GetSpace("Main Menu");
      

      // Get the camera information
      TransformPtr cameraInfo = mainMenu->GetCamera()->GET_COMPONENT(Transform);
      cameraInfo->scale = { cameraInfo->scale.x * .1f, cameraInfo->scale.y * .1f };
      glm::vec2 cameraPos = cameraInfo->position;
      glm::vec2 cameraSize = cameraInfo->scale;

      // Add a green start button
      EntityPtr start = ENGINE->Factory().create("Main Menu Start");
      start->GET_COMPONENT(Transform)->position = { cameraSize.x * .2f, cameraSize.y * .2f };

      // add the button to the space
      mainMenu->AddEntity(start);

      // Add a red exit button
      EntityPtr exit = ENGINE->Factory().create("Main Menu Exit");
      exit->GET_COMPONENT(Transform)->position = { -cameraSize.x * .2f, cameraSize.y * .2f };

      // add the button to the space
      mainMenu->AddEntity(exit);

      // Add a yellow credits button
      EntityPtr credits = ENGINE->Factory().create("Main Menu Credits");
      credits->GET_COMPONENT(Transform)->position = { 0.f, - cameraSize.y * .2f };

      // add the button to the space
      mainMenu->AddEntity(credits);

      // Add a yellow how to play button
      EntityPtr howToPlay = ENGINE->Factory().create("Main Menu How To Play");
      howToPlay->GET_COMPONENT(Transform)->position = { cameraSize.x * .3f, -cameraSize.y * .2f };

      // add the button to the space
      mainMenu->AddEntity(howToPlay);

      // Add a yellow settings button
      EntityPtr settings = ENGINE->Factory().create("Main Menu Settings");
      settings->GET_COMPONENT(Transform)->position = { -cameraSize.x * .3f, -cameraSize.y * .2f };

      // add the button to the space
      mainMenu->AddEntity(settings);

    }

  } // Gamestates

} // AlJeEngine
