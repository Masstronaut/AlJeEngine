
/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "Component.h"

namespace AlJeEngine
{

  enum EnumeratedSystem
  {

    ES_MAX
  };

  typedef EnumeratedSystem ESys;


  struct System
  {

    virtual void   Init() = 0;
    virtual void   Update(float) = 0;
    virtual void   Shutdown() = 0;
    void   RegisterComponent(BitfieldComponent);
    friend  struct Engine;

    inline  mask   Mask()
    {
      return _mask;
    }


  protected:
    mask _mask;
    std::vector < std::shared_ptr < Entity > > _entities;
    // Basic system metadata
    ESys _type;
    std::string _name;
  };

}; //AlJeEngine
