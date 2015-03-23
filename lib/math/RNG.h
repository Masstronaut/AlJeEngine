/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
* @brief The Engine class is the core of the game engine.
*
*/
#pragma once
#include <random>
#define PI 3.1415926535f
#define DEG2RAD 0.0174532925f
#define RAD2DEG 57.2957795f
float RandFloat()
{
  float ret = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return ret;
}