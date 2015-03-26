/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/

#include <vector>
#include <string>
#include <memory>

#include "Space.h"
#include "System.h"

namespace AlJeEngine
{

  enum GamestateType
  {
    GS_MainMenu,
    GS_PauseMenu,
    GS_TestDemo,
  };

  class Gamestate : public System
  {

  public:

    Gamestate(std::string name, GamestateType GST)
      : System(name, ES_Gamestate), _state(GST)
    {
    }

    virtual ~Gamestate() {}

    virtual void Init() = 0;

    virtual void Update() = 0;

    virtual void Shutdown() = 0;

    virtual void PoppedTo(GamestateType) {}

    GamestateType State() const 
    { 
      return _state; 
    }

    inline void RegisterSpace(SpacePtr space)
    {
      _spaces.push_back(space->Name());
    }

    inline const std::vector<std::string>& GetSpaces() const
    {
      return _spaces;
    }

  private:
    std::vector<std::string> _spaces;
    const GamestateType _state;
  };

  typedef std::shared_ptr<Gamestate> GamestatePtr;

} // AlJeEngine
