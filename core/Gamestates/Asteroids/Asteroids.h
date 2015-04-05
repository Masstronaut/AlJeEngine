
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <memory>
#include "../../engine/headers/Gamestate.h"
#include "../../engine/headers/System.h"
#include "../../components/Components.h"
namespace AlJeEngine
{
  namespace Gamestates
  {

    class Asteroids : public Gamestate
    {
    public:
      Asteroids() : Gamestate("Asteroids Gamestate", GS_Asteroids) 
      {
        /* the engine calls init manually, 
        which should typically take the place of most of the constructor. */
      }

      ~Asteroids() {}
      void Init();

      void Update(float);
      
      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:

    };

    typedef std::shared_ptr<Asteroids> AsteroidsPtr;

  }; // Systems

}; // AlJeEngine

