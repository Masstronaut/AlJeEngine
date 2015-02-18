
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <chrono>
namespace AlJeEngine
{
  namespace Time
  {

    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::time_point< std::chrono::high_resolution_clock > timePoint;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::microseconds us;
    typedef std::chrono::duration<float> floatSeconds;


  }

}