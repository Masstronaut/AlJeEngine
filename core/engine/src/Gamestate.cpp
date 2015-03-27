#include "..\headers\Gamestate.h"
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

namespace AlJeEngine
{



bool Gamestate::CheckSpaceActive(std::string name)
{
  for (auto it : _spaces)
    if (it == name)
      return true;
  return false;
}

void Gamestate::SetLogicalSpace(std::string name)
{
  _LogicalSpace = name;
}

} // AlJeEngine
