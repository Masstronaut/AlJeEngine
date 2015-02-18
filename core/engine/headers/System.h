
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
#pragma region metadataEnums 
  enum EnumeratedSystem
  {
    ES_Test,
    ES_MAX
  };
#pragma endregion

  typedef EnumeratedSystem ESys;


  struct System
  {
    System(std::string &name, ESys type) 
          :
          _name(name),
          _type(type)
          {
          }
    virtual void   Init() = 0;
    virtual void   Update(float) = 0;
    virtual void   Shutdown() = 0;
    void   RegisterComponent(BitfieldComponent);
    friend  struct Engine;

    inline  mask   Mask()
    {
      return _mask;
    }

    friend class Space;
  protected:
    mask        _mask;
    EntityVec   _entities;
    // Basic system metadata
    ESys        _type;
    std::string _name;
  };

  // typedef magic! AKA laziness
  typedef std::shared_ptr< System > SystemPtr;
  typedef std::vector< SystemPtr > SystemVec;
}; //AlJeEngine
