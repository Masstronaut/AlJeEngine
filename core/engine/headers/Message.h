
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once

namespace AlJeEngine
{
  namespace Message
  {
    typedef unsigned Message;

    enum MessageValues
    {
      // These message values are used to specify what type of collision has occurred.
      MV_AABBAABB,
      MV_AABBCircle,
      MV_CircleCircle,

      // These message values are for game-related key press events.
      MV_Down,
      MV_Up,
      MV_Left,
      MV_Right,
      MV_Space,

      // These message values are for when the mouse collides with an object.
      // NOTE: The second EntityPtr with these messages will always be null.
      // The first EntityPtr will be the collided object.
      MV_MouseHover,
      MV_MouseClick,

      // These message values are for control flow of the program.
      MV_BackButton, // this could be esc or back on a controller.
      MV_SelectButton,
      MV_PauseButton,

      //These messages are for gamestate operations
      MV_PopGamestate,

      MV_ToggleFullScreen,

      // This is a gameplay related message. It is sent when a game object is destroyed.
      // The first entity is the object that was killed.
      // The second entity is the object that killed it and caused the death, if one exists.
      MV_ObjectKilled,
    };


  } // Message


}; //AlJeEngine
