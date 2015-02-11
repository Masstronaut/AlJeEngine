

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
  EC_Transform,
  EC_Drawable,
  EC_RigidBody,

  EC_Max
};

enum BitfieldComponent
{
  MC_Alive = 1,
  MC_Transform = 1 << 1,
  MC_Drawable = 1 << 2,
  MC_RigidBody = 1 << 3


};

struct Component
{
  const EnumeratedComponent _type;
  const BitfieldComponent   _mask;
  
};
