

/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <vector>
#include <memory>
#include "../../lib/math/glm/glm.hpp"
#include "../../lib/math/headers/affmath.h"
#include "../engine/headers/Component.h"

namespace AlJeEngine
{
   
    enum ColliderType
    {
      Circle,
      Box,
      Poly,
      none
    };

    struct Collider : public Component
    {
      Collider(ColliderType type) : Component(EC_Collider, MC_Collider), _colliderType(type) {}
      const ColliderType _colliderType;



      // this is a disgusting function. You should come up with a more elegant solution!
      template<typename T>
      std::shared_ptr<T> GetDerivedCollider(ComponentPtr me);

    };

    struct CircleCollider : public Collider
    {
      CircleCollider() : Collider(Circle) {}
      float radius = 1.f;
    };
    
    struct BoxCollider : public Collider
    {
      BoxCollider() : Collider(Box) {}
      float height = 1.f;
      float width = 1.f;
    };
  
    struct PolyCollider : public Collider
    {
      PolyCollider() : Collider(Poly) {}
      std::vector<glm::vec2> points;
    };


    typedef std::shared_ptr<Collider> ColliderPtr;
    typedef std::shared_ptr<CircleCollider> CircleColliderPtr;
    typedef std::shared_ptr<BoxCollider> BoxColliderPtr;
    typedef std::shared_ptr<BoxCollider> BoxColliderPtr;




    template<typename T>
    std::shared_ptr<T> Collider::GetDerivedCollider(ComponentPtr me)
    {
      if (me.get() != this)
        throw std::bad_cast("Failed attempt for a collider to cast itself to the derived type.");

      switch (_colliderType)
      {
      case(Circle):
        return std::static_pointer_cast<CircleCollider>(me);
        break;
      case(Box):
        return std::static_pointer_cast<BoxCollider>(me);
        break;
      case(Poly):
        return std::static_pointer_cast<PolyCollider>(me);
        break;
      default:
        throw std::bad_cast("Failed attempt for a collider to cast itself to the derived type.");
        break;

      }
      

    }

}; // namespace AlJe