
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 */

#pragma once

#include "Component.h"

enum EnumeratedSystem
{

  ES_MAX
};

typedef EnumeratedSystem ESys;


struct System
{
  
  virtual void Init              (                   ) = 0;
  virtual void Update            ( float             ) = 0;
  virtual void Shutdown          (                   ) = 0;

          void RegisterComponent ( BitfieldComponent );

friend class Engine;

protected:
  mask _mask;

  // Basic system metadata
  ESys _type;
  std::string _name;
};
