/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../SystemsInclude.h"
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void ButtonController::Init()
    {
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_BoxCollider);
      RegisterComponent(MC_RigidBody);
      RegisterComponent(MC_MenuObject);
      RegisterComponent(MC_Transform);
    }

    void ButtonController::Update(float dt)
    {
      for (auto it : _entities)
      {
        SpritePtr sprite = it->GET_COMPONENT(Sprite);
        MenuObjectPtr menuObj = it->GET_COMPONENT(MenuObject);

        if (menuObj->_hovered)
        {
          menuObj->_hovered = false;
          break;
        }

        sprite->_color = menuObj->_neutralColor;

      }
    }

    void ButtonController::Shutdown()
    {

    }

    void ButtonController::SendMsg(EntityPtr e1, EntityPtr, Message::Message message)
    {
      // Verify that an entity was included in the message
      if (!e1)
        return;
      // verify that the message is about a button.
      if (!e1->CheckMask(MC_BoxCollider | MC_MenuObject | MC_Sprite | MC_Transform | MC_RigidBody))
        return;
      SpritePtr sprite = e1->GET_COMPONENT(Sprite);
      MenuObjectPtr menuObj = e1->GET_COMPONENT(MenuObject);
      switch (message)
      {
      case Message::MV_MouseHover:
        sprite->_color = menuObj->_hoverColor;
        menuObj->_hovered = true;
        break;
        
      default:
        break;
      }
    }

  } // Systems

} // AlJeEngine