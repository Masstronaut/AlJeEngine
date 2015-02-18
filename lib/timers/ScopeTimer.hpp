
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <chrono>
#include "TimeDefines.h"
namespace AlJeEngine
{
  namespace Time
  {

    class ScopeTimer
    {
    public:
      // when the timer is initialized, get the current time.
      ScopeTimer(float *output) : start(clock::now()), retval(output) {}

      // when the timer leaves scope, get the end time, 
      // convert the duration to a float where 1.f = 1 second,
      // then store the result in the pointer specified at initialization.
      ~ScopeTimer()
      {
        end = clock::now();
        floatSeconds duration = end - start;
        *retval = duration.count();
      }


    private:
      timePoint start;
      timePoint end;

      float *retval;
    };

  }; // Time
}; // AlJeEngine