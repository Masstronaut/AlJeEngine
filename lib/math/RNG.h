/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#pragma once
#include <random>
// These defines aren't actually RNG related, but they are convenient constants.
#define PI 3.1415926535f
#define DEG2RAD 0.0174532925f
#define RAD2DEG 57.2957795f

/*!
* @brief Generates a random float between 0.f and 1.f
*
* @return Returns the randomly generated float.
*/
float RandFloat();