/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 */

#include "../headers/ArchetypeFactory.h"


namespace AlJeEngine
{
  using namespace Archetypes;

  ArchetypeFactory::ArchetypeFactory()
  {
    // This is where you add the archetype creation functions to the factory.

    addArchetype("DefaultCamera",          DefaultCamera);
    addArchetype("Box",                    BoxGameObject);
    addArchetype("Circle",                 CircleGameObject);
    addArchetype("Box Particle",           BoxParticleObject);
    addArchetype("Fire Particle",          FireParticleObject);
    addArchetype("Circle Particle",        CircleParticleObject);
                                           
    // Main Menu button archetypes              
    addArchetype("Main Menu Exit",         MainMenuExit);
    addArchetype("Main Menu Start",        MainMenuStart);
    addArchetype("Main Menu Credits",      MainMenuCredits);
    addArchetype("Main Menu How To Play",  MainMenuHowToPlay);
    addArchetype("Main Menu Settings",     MainMenuSettings);

    // Pause menu button archetypes
    addArchetype("Pause Menu Resume",      PauseMenuResume);
    addArchetype("Pause Menu Quit",        PauseMenuQuit);
    addArchetype("Pause Menu Restart",     PauseMenuRestart);
    addArchetype("Pause Menu Options",     PauseMenuOptions);

    // Asteroids gameplay archetypes
    addArchetype("Player",                 Player);
    addArchetype("Bullet",                 PlayerBullet);
    addArchetype("Asteroid",               Asteroid);

  }

  void ArchetypeFactory::addArchetype(std::string archetype, CreateArchetypeFn creator)
  {
    _archetypes.emplace(archetype, creator);
  }

  EntityPtr ArchetypeFactory::create(std::string archetype)
  {
    // Search for the archetype
    std::unordered_map<std::string, CreateArchetypeFn>::iterator it = _archetypes.find(archetype);

    // Check if the archetype was found. If it was, we can return a new instance of the archetype.
    if (it != _archetypes.end())
      return it->second();

    // If the archetype wasn't found, throw a range error with a message about what happened.
    throw std::range_error("Tried to create an archetype that doesn't exist: " + archetype);

  }
}; //AlJeEngine
