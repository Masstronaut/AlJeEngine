
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
    }

    void PhysicsDetect::Update(float dt)
    {
      // This has to use actual iterators in order to get the current entity's position in the space.
      for (auto obj1 = _entities.begin(); obj1 != _entities.end(); ++obj1)
      {
        // Due to operator precedence, we must do (*it) so the iterator is dereferenced first.
        TransformPtr transform = (*obj1)->GET_COMPONENT(Transform);
        glm::vec2* position = &transform->position;

        for (auto obj2 = obj1 + 1; obj2 != _entities.end(); ++obj2)
        {
          // do some collision stuff
        }




      }
    }

    void PhysicsDetect::Shutdown()
    {

    }

    bool PhysicsDetect::AABBCheck(EntityPtr e1, EntityPtr e2)
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
            return 1;
          return 0;
        }


  } // Systems

} // AlJeEngine