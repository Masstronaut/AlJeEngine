/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include "Entity.h"
#include "../../components/Components.h"


namespace AlJeEngine
{
    // The generic function to create an archetype.
    // The function type is CreateArchetypeFn, it takes void and returns an EntityPtr.
    typedef EntityPtr (*CreateArchetypeFn)();

  namespace Archetypes
  {

    EntityPtr DefaultCamera();

    EntityPtr BoxGameObject();


  } // Archetypes

} //AlJeEngine
