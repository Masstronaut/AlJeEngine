
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include "Asteroids.h"
#include "../../engine/headers/Engine.h"
#include "../../components/Components.h"
#include "../../systems/SystemsInclude.h"
#include <math.h> // sin and cos
#include <sstream>
#include <cstdlib> // rand, srand
#include <time.h> // seeding rand
#include "../../lib/math/RNG.h" // randfloat

namespace AlJeEngine
{
  extern Engine* ENGINE;

  using namespace Systems;
  namespace Gamestates
  {

      
    void Asteroids::Init()
    {
      // Register the spaces that should be updated with this system.
      RegisterSpace("Game World");

      // Set which space this gamestate's Update() function should be used with.
      SetLogicalSpace("Game World");

      SpacePtr gameworld = ENGINE->GetSpace("Game World");
      
      // clear out any pre-existing entities and systems from the space.
      gameworld->Clear();

      gameworld->AddSystem(GETSYS(CameraSystem));
      gameworld->AddSystem(GETSYS(GLGraphics));

      // Register for drawable objects
      RegisterComponent(MC_Transform);
      RegisterComponent(MC_Sprite);
      RegisterComponent(MC_Particle);
  
    }

    void Asteroids::Update(float dt)
    {
      
    }

    void Asteroids::Shutdown()
    {
      if (ENGINE->SpaceExists("Game World"))
      {
        ENGINE->GetSpace("Game World")->Clear();
      }

    }

    

    void Asteroids::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message)
    {

      switch (message)
      {
      case(Message::MV_Up) :
        
        break;
      case(Message::MV_Down) :
        
        break;
      case(Message::MV_Left) :
        
        break;
      case(Message::MV_Right) :
        
        break;

      case(Message::MV_BackButton) :
        ENGINE->PushGamestate(PauseMenuPtr(new PauseMenu()));
        break;

      case(Message::MV_PopGamestate) :
        ENGINE->PopGamestate();
        break;

      default:
        break;
      }
    }

  } // Systems

} // AlJeEngine