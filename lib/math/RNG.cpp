/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#include "RNG.h"
#include <time.h>
static bool seeded = false;
void seed()
{
  if (!seeded)
  {
    srand(time(NULL));
    seeded = true;
  }
}

float RandFloat()
{
  // This function insures that the RNG is always seeded exactly once.
  seed();
  
  // This works by getting a random number and dividing it by the maximum random number.
  // The value will always be between 0.f and 1.f
  float ret = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return ret;
}