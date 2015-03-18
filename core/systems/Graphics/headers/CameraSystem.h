/**
* @author Jeffrey Uong
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include <memory>

#include "../../../engine/headers/System.h"

namespace AlJeEngine
{
  namespace Systems
  {
    class CameraSystem : public System
    {
    public:
      CameraSystem();

      void Init();
      void Update(float);
      void Shutdown();



    private:

    };

    typedef std::shared_ptr<CameraSystem> CameraSystemPtr;

  } // Systems

} // AlJeEngine

#endif

