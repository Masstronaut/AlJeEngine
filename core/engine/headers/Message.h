
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

    };


  } // Message


}; //AlJeEngine
