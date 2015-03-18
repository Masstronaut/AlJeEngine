
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


    };


  } // Message


}; //AlJeEngine
