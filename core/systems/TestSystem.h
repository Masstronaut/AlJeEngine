
/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#pragma once
#include <memory>

#include "../engine/headers/System.h"
#include "../components/Components.h"
namespace AlJeEngine
{
  namespace Systems
  {

    class Test : public System
    {
    public:
      Test() : System(std::string("Test System"), ES_Test) {/* the engine calls init manually, which should take the place of most of the constructor. */}

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

