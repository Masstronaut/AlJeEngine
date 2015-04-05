
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
      MV_AABBAABB     = 1,
      MV_AABBCircle   = 1 <<  1, // 2
      MV_CircleCircle = 1 <<  2, // 4

      // These message values are for game-related key press events.
      MV_Down         = 1 <<  3, // 8
      MV_Up           = 1 <<  4, // 16
      MV_Left         = 1 <<  5, // 32
      MV_Right        = 1 <<  6, // 64

      // These message values are for when the mouse collides with an object.
      // NOTE: The second EntityPtr with these messages will always be null.
      // The first EntityPtr will be the collided object.
      MV_MouseHover   = 1 <<  7,
      MV_MouseClick   = 1 <<  8,

      // These message values are for control flow of the program.
      MV_BackButton   = 1 <<  9, // this could be esc or back on a controller.
      MV_SelectButton = 1 << 10,
      MV_PauseButton  = 1 << 11,

      //These messages are for gamestate operations
      MV_PopGamestate = 1 << 12,

      MV_ToggleFullScreen = 1 << 13,

      // This is a gameplay related message. It is sent when a game object is destroyed.
      // The first entity is the object that was killed.
      // The second entity is the object that killed it and caused the death, if one exists.
      MV_ObjectKilled = 1 << 14,
    };


  } // Message


}; //AlJeEngine
