

/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 * 
 */

#pragma once
#include <memory>
namespace AlJeEngine
{

  typedef unsigned mask;
#pragma region metadataEnums

  /*!
  * @brief The EnumeratedComponent is used for indexing components.
  * The value of the enum is the index on the entity of the component.
  */
  enum EnumeratedComponent
  {
    EC_None           =  0,
    EC_Drawable       =  1,
    EC_RigidBody      =  2,
    EC_Sprite         =  3,
    EC_BoxCollider    =  4,
    EC_CircleCollider =  5,
    EC_Camera         =  6,
    EC_Transform      =  7,
    EC_Particle       =  8,
    EC_MenuObject     =  9,
    EC_Bullet         = 10,
    EC_Parent         = 11,
    EC_Weapon         = 12,
    EC_Health         = 13,
    EC_Score          = 14,
    EC_Lifetime       = 15,

    // This will correspond to the maximum number of components that exist.
    EC_Max,

  };

  /*!
  * @brief The BitfieldComponent is used for rapidly checking which components are attached to an entity.
  * They can be ORed together (IE MC_Alive | MC_Transform) 
  * to check an entity for multiple components in a single compare. 
  */
  enum BitfieldComponent
  {
    MC_Alive           =  1,
    MC_Transform       =  1 <<  1,
    MC_Drawable        =  1 <<  2,
    MC_RigidBody       =  1 <<  3,
    MC_Sprite          =  1 <<  4,
    MC_BoxCollider     =  1 <<  5,
    MC_CircleCollider  =  1 <<  6,
    MC_Camera          =  1 <<  7,
    MC_Particle        =  1 <<  8,
    MC_MenuObject      =  1 <<  9,
    MC_Bullet          =  1 << 10,
    MC_Parent          =  1 << 11,
    MC_Weapon          =  1 << 12,
    MC_Health          =  1 << 13,
    MC_Score           =  1 << 14,
    MC_Lifetime        =  1 << 15,

    // This is used when a system doesn't wish to recieve any objects.
    MC_NOOBJECTS       = -1,
  };
#pragma endregion


  struct Component
  {
    Component(EnumeratedComponent type, BitfieldComponent mask) : _type(type), _mask(mask) {}

    // These are const because once the component is created, it should never change types.
    const EnumeratedComponent _type;
    const BitfieldComponent   _mask;

    // this must be virtual to makes sure derived component types are deallocated properly.
    virtual ~Component() {}

  private:
    // no default construction is allowed. Components MUST have a type and mask.
    Component() = delete;
  };

  typedef std::shared_ptr<Component> ComponentPtr;

}; // AlJeEngine
