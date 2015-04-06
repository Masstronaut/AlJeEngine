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
  seed();
  float ret = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return ret;
}