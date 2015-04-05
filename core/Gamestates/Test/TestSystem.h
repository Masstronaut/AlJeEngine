
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
#include "../../components/ComponentsInclude.h"
namespace AlJeEngine
{
  namespace Gamestates
  {

    class Test : public Gamestate
    {
    public:
      Test() : Gamestate("Test Demo Gamestate", GS_TestDemo) 
      {
        /* the engine calls init manually, 
        which should typically take the place of most of the constructor. */
      }

      ~Test() {}
      void Init();

      void Update(float);
      
      void Shutdown();

      void SendMsg(EntityPtr, EntityPtr, Message::Message);

    private:
      void PretzelInit(unsigned);
      void PretzelDemo(float);

      void FireBallInit(unsigned);
      void FireBallDemo(float);
      void FireBallSpawn(unsigned);

      void ExplosionInit(unsigned);
      void ExplosionDemo(float);
      void ExplosionSpawn(unsigned);


      float timeAccumulator = 0.f;
    };

    typedef std::shared_ptr<Test> TestPtr;

  }; // Systems

}; // AlJeEngine

