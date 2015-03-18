
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
#include "Message.h"

namespace AlJeEngine
{
#pragma region metadataEnums 
  enum EnumeratedSystem
  {
    ES_Test,
    ES_WindowSDL,
    ES_GLGraphics,
    ES_Render,
    ES_CameraSystem,
    ES_PhysicsDetect,

    // this should always be last
    ES_MAX
  };
#pragma endregion

  typedef EnumeratedSystem ESys;


  struct System
  {
    System(std::string &name, ESys type) 
          :
          _name(name),
          _type(type),
          _mask(MC_Alive)
          {
          }
    virtual void   Init() = 0;
    virtual void   Update(float) = 0;
    virtual void   Shutdown() = 0;

    // Implementing this function in a derived system is optional.
    // If it is not implemented, the system won't receive any messages
    virtual void SendMsg(EntityPtr, EntityPtr, Message::Message) {}


    void RegisterComponent(BitfieldComponent);

    inline mask   Mask() { return _mask; }

    friend class Space;
    friend  struct Engine;
  protected:
    mask        _mask;
    EntityVec   _entities;
    // Basic system metadata
    const ESys  _type;
    std::string _name;
  };

  // typedef magic! AKA laziness
  typedef std::shared_ptr< System > SystemPtr;
  typedef std::vector< SystemPtr > SystemVec;
}; //AlJeEngine
