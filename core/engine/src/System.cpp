/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include "../headers/System.h"


namespace AlJeEngine
{

  void System::RegisterComponent(BitfieldComponent bc)
  {
    _mask |= bc;
  }


}; //AlJeEngine
