/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#pragma once
#include "Entity.h"
#include "../../components/ComponentsInclude.h"


namespace AlJeEngine
{
    // The generic function to create an archetype.
    // The function type is CreateArchetypeFn, it takes void and returns an EntityPtr.
    typedef EntityPtr (*CreateArchetypeFn)();

  namespace Archetypes
  {
    // These are pretty self explanatory, so I won't be documenting them all individually.
    // If you feel this is the wrong decision, feel free to document them yourself and make a pull request.


    EntityPtr DefaultCamera();

    EntityPtr BoxGameObject();
    EntityPtr BoxParticleObject();

    EntityPtr CircleGameObject();
    EntityPtr CircleParticleObject();

    EntityPtr FireParticleObject();

    EntityPtr GenericMenuObject();

    /*     Menu Objects      */
    // Main menu
    EntityPtr MainMenuExit();
    EntityPtr MainMenuStart();
    EntityPtr MainMenuCredits();
    EntityPtr MainMenuHowToPlay();
    EntityPtr MainMenuSettings();

    // Pause menu
    EntityPtr PauseMenuResume();
    EntityPtr PauseMenuQuit();
    EntityPtr PauseMenuRestart();
    EntityPtr PauseMenuOptions();

    /*     Gameplay Objects    */
    EntityPtr PlayerBullet();
    EntityPtr Player();
    EntityPtr Asteroid();

  } // Archetypes

} //AlJeEngine
