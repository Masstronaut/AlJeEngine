/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../SystemsInclude.h"
#include <math.h> // sin and cos
namespace AlJeEngine
{
  extern Engine* ENGINE;

  namespace Systems
  {

      
    void PhysicsDetect::Init()
    {
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_BoxCollider);
      RegisterComponent(MC_RigidBody);
    }

    void PhysicsDetect::Update(float dt)
    {
      CheckMouseCollisions();

      // This has to use actual iterators in order to get the current entity's position in the space.
      for (auto obj1 = _entities.begin(); obj1 != _entities.end(); ++obj1)
      {
        // Due to operator precedence, we must do (*it) so the iterator is dereferenced first.

        // Get the transform data for the first object.
        TransformPtr obj1Trans = (*obj1)->GET_COMPONENT(Transform);
        glm::vec2* obj1Pos = &obj1Trans->position;
        // store the collider type of the object.
        EnumeratedComponent obj1ColliderType = (*obj1)->Collider();

        for (auto obj2 = obj1; obj2 != _entities.end(); ++obj2)
        {
          if (obj2 == obj1)
            continue;
          // Get the transform data for the second object.
          TransformPtr obj2Trans = (*obj2)->GET_COMPONENT(Transform);
          glm::vec2* obj2Pos = &obj2Trans->position;
          // store the collider type of the object.
          EnumeratedComponent obj2ColliderType = (*obj1)->Collider();
          
          
          // do some collision stuff
          bool collisionFound;
          // Determine what type of collision check should be done.
          switch (obj1ColliderType)
          {
          case(EC_BoxCollider) :
            switch (obj2ColliderType)
            {
            case(EC_BoxCollider) :
              collisionFound = AABBAABBCheck(*obj1, *obj2);
              break;
            case(EC_CircleCollider) :
              collisionFound = AABBCircleCheck(*obj1, *obj2);
              break;
            default:
              // This is the case where an object has no collider.
              break;

            } 
            break;// obj1 box collider

          case(EC_CircleCollider):
            switch (obj2ColliderType)
            {
            case(EC_BoxCollider) :
              // We have to switch their order because it takes the AABB object first.
              collisionFound = AABBCircleCheck(*obj2, *obj1);
              break;
            case(EC_CircleCollider) :
              collisionFound = CircleCircleCheck(*obj1, *obj2);
              break;
            default:
              // This is the case where an object has no collider.
              break;

            }
            break; // obj1 circle collider
          default:
            break;

          }

        }




      }
    }

    void PhysicsDetect::Shutdown()
    {

    }

    void PhysicsDetect::SendMsg(EntityPtr, EntityPtr, Message::Message)
    {

    }

    bool PhysicsDetect::AABBAABBCheck(EntityPtr e1, EntityPtr e2)
    {
      // get the transform pointers in a more accessible way.
      TransformPtr t1 = (e1)->GET_COMPONENT(Transform);
      TransformPtr t2 = (e2)->GET_COMPONENT(Transform);

      // Get the box collider for both objects
      BoxColliderPtr bc1 = e1->GET_COMPONENT(BoxCollider);
      BoxColliderPtr bc2 = e2->GET_COMPONENT(BoxCollider);

      // Get the square distance between the center of each object along the x and y axis.
      float xdist = (t1->position.x - t2->position.x) * (t1->position.x - t2->position.x);
      float ydist = (t1->position.y - t2->position.y) * (t1->position.y - t2->position.y);

      // Get the sum of the width and height of the objects.
      float widths = bc1->width + bc2->width;
      float heights = bc1->height + bc2->height;

      // check if the distance between the centers is less than the size of the boxes.
      if (xdist <= widths * widths && ydist <= heights * heights)
      {
        ENGINE->SendMsg(e1, e2, Message::MV_AABBAABB);
        return 1;
      }
      return 0;
    }


    bool PhysicsDetect::AABBCircleCheck(EntityPtr box, EntityPtr circle)
    {
      glm::vec2 boxPos = box->GET_COMPONENT(Transform)->position;
      glm::vec2 circleCenter = circle->GET_COMPONENT(Transform)->position;
      BoxColliderPtr boxCollider = box->GET_COMPONENT(BoxCollider);
      float radius = circle->GET_COMPONENT(CircleCollider)->radius;

      glm::vec2 nearestPoint = circleCenter;

      float boxTop = boxPos.y + boxCollider->height * 0.5f;
      float boxBot = boxPos.y - boxCollider->height * 0.5f;
      float boxLeft = boxPos.x - boxCollider->width * 0.5f;
      float boxRight = boxPos.x + boxCollider->width * 0.5f;

      if      (nearestPoint.x < boxLeft)  nearestPoint.x = boxLeft;
      else if (nearestPoint.x > boxRight) nearestPoint.x = boxRight;
      if      (nearestPoint.y < boxBot)   nearestPoint.y = boxBot;
      else if (nearestPoint.y > boxTop)   nearestPoint.y = boxTop;


      if (glm::distance(nearestPoint, circleCenter) < radius)
      {
        ENGINE->SendMsg(box, circle, Message::MV_AABBCircle);
        return 1;
      }
      return 0;
    }

    bool PhysicsDetect::CircleCircleCheck(EntityPtr e1, EntityPtr e2)
    {
      glm::vec2 e1Pos = e1->GET_COMPONENT(Transform)->position;
      glm::vec2 e2Pos = e2->GET_COMPONENT(Transform)->position;
      float e1radius = e1->GET_COMPONENT(CircleCollider)->radius;
      float e2radius = e2->GET_COMPONENT(CircleCollider)->radius;

      float radii = e1radius * e1radius + e2radius * e2radius;
      float distance = glm::distance(e1Pos, e2Pos);

      if (radii >= distance)
      {
        ENGINE->SendMsg(e1, e2, Message::MV_CircleCircle);
        return 1;
      }

      return 0;
    }

    bool PhysicsDetect::AABBPointCheck(EntityPtr entity, glm::vec2 point)
    {
      // Get easy access to the parts of the entity we want.
      glm::vec2 boxCenter = entity->GET_COMPONENT(Transform)->position;
      BoxColliderPtr boxCollider = entity->GET_COMPONENT(BoxCollider);
      // make a variable to store each side of the AABB.
      float left, right, up, down;

      // compute each side of the box collider
      left  = boxCenter.x - (boxCollider->width  * 0.5f);
      right = boxCenter.x + (boxCollider->width  * 0.5f);
      up    = boxCenter.y + (boxCollider->height * 0.5f);
      down  = boxCenter.y - (boxCollider->height * 0.5f);

      // check if the point is inside the box
      if ( point.x < right && point.x > left // check the x axis
        && point.y < up    && point.y > down)// check the y axis
        return true;
      
      // If we get here the collision check failed (no collision).
      return false;
    }

    bool PhysicsDetect::CirclePointCheck(EntityPtr entity, glm::vec2 point)
    {
      float radius = entity->GET_COMPONENT(CircleCollider)->radius;
      float radiusSQ = radius * radius;
      glm::vec2 circleCenter = entity->GET_COMPONENT(Transform)->position;

      // Compute the distance on each axis
      float xdist = circleCenter.x - point.x;
      float ydist = circleCenter.y - point.y;

      // compute the square distance
      float distanceSQ = xdist * xdist + ydist * ydist;

      // check if the distance is less than the size of the circle
      if (distanceSQ < radiusSQ)
        return true;

      // Check if the distance is less than 
      return false;
    }

    void PhysicsDetect::CheckMouseCollisions()
    {
      // check all the objects for a collision with the mouse:
      glm::vec2 mousePos = GETSYS(WindowSDL)->GetMousePosition();
      bool mouseClicked = GETSYS(WindowSDL)->GetMouseTrigger();

      for (auto obj : _entities) // equivalent to: for (auto obj = _entities.begin(); obj != _entities.end(); ++obj) auto obj = *obj;
      {
        EnumeratedComponent colliderType = obj->Collider();
        bool collision = false;
        switch (colliderType)
        {
        case(EC_BoxCollider) :
          collision = AABBPointCheck(obj, mousePos);
          break;
        case(EC_CircleCollider) :
          collision = CirclePointCheck(obj, mousePos);
          break;

        default:
          break;
        }

        if (collision)
        {
          if (mouseClicked)
            ENGINE->SendMsg(obj, nullptr, Message::MV_MouseClick);
          else
            ENGINE->SendMsg(obj, nullptr, Message::MV_MouseHover);
        }

      }
    }

  } // Systems

} // AlJeEngine