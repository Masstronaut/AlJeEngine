
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
      MV_AABBCircle   = 1 <<  1,
      MV_CircleCircle = 1 <<  2,

      // These message values are for game-related key press events.
      MV_Down         = 1 <<  3,
      MV_Up           = 1 <<  4,
      MV_Left         = 1 <<  5,
      MV_Right        = 1 <<  6,

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


    };


  } // Message


}; //AlJeEngine
