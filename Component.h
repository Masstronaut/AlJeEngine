

/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 */

#pragma once

typedef unsigned mask;

enum EnumeratedComponent
{


  EC_Max
};

enum BitfieldComponent
{



};

struct Component
{
  const EnumeratedComponent _type;
  const BitfieldComponent   _mask;
  
};
