
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
    // Window handler
    ES_WindowSDL,

    // Graphics systems
    ES_GLGraphics,
    ES_CameraSystem,

    // Physics systems
    ES_PhysicsDetect,
    ES_Movement,

    // Menu systems
    ES_ButtonController,
    

    //Gameplay systems
    ES_BulletController,
    ES_WeaponController,


    ES_Gamestate,
    // this should always be last
    ES_MAX
  };
#pragma endregion

  typedef EnumeratedSystem ESys;


  struct System
  {
    /*!
    * @brief Constructs a base System class instance.
    *
    * @param name The name of the system.
    * @param type The type of the system.
    */
    System(std::string &name, ESys type) 
          :
          _name(name),
          _type(type),
          _mask(MC_Alive)
          {
          }

    /*!
    * @brief The system destructor.
    * @note This must be virtual to ensure proper deletion of derived system types.
    */
    virtual ~System() {}
    
    /*!
    * @brief This is a pure virtual function defining the interface of a System.
    * This function will be called once by the Engine when this System is created.
    * @note This function must be implemented in any derived classes.
    */
    virtual void   Init() = 0;

    /*!
    * @brief This is a pure virtual function defining the interface of a System.
    * This function will be called once per frame per space this system is attached to.
    * @note This function must be implemented in any derived classes.
    */
    virtual void   Update(float) = 0;

    /*!
    * @brief This is a pure virtual function defining the interface of a System.
    * This function will be called once by the Engine when this System is being destroyed.
    * @note This function must be implemented in any derived classes.
    */
    virtual void   Shutdown() = 0;

    /*!
    * @brief This is the interface used to send messages to the System.
    * @note this function is optional, and systems that don't need any messages can ignore it.
    *
    * @param e1 The optional first entity of the message. 
    * @param e2 The optional second entity of the message.
    * @note Depending on the message, there may be 0, 1, or 2 entitites sent with the message.
    * @param message The message being sent.
    */
    virtual void SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message) {}

    /*!
    * @brief Specifies that a specific component type is required for the system to function.
    *
    * @param component The component being registered as a requirement to run.
    */
    inline void RegisterComponent(BitfieldComponent component);

    /*!
    * @brief exposes the component requirements of the System.
    * @note the engine automatically pre-fills the system's _entities member 
    * with all entities in the current space that meet the mask requirements.
    *
    * @return Returns the system's mask.
    */
    inline mask   Mask() { return _mask; }

    friend class Space;
    friend  struct Engine;
  protected:
    mask        _mask;
    EntityVec   _entities;
    // Basic system metadata
    const ESys  _type;
    std::string _name;

  private:
    // Default construction of a system is not allowed.
    // Systems MUST have a name and type.
    System() = delete;
  };

  // typedef magic! AKA laziness
  typedef std::shared_ptr< System > SystemPtr;
  typedef std::vector< SystemPtr > SystemVec;
}; //AlJeEngine
