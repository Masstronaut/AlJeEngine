

/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 */
 
#include "System.h"

void System::RegisterComponent ( BitfieldComponent bc)
{
  _mask |= bc;
}