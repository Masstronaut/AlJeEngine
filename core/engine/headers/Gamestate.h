/**
* @author Allan Deutsch
* @version 0.5
* @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
*
*/
#pragma once
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

    virtual void Update(float) = 0;

    virtual void Shutdown() = 0;

    virtual void PoppedTo(GamestateType) {}

    inline GamestateType State() const 
    { 
      return _state; 
    }


    inline const std::vector<std::string>& GetSpaces() const
    {
      return _spaces;
    }

    const std::string& GetLogicalSpace() 
    { 
      return _LogicalSpace; 
    }

    bool CheckSpaceActive(std::string);

  private:
    // These are the spaces that will be updated while this is the active gamestate.
    std::vector<std::string> _spaces;

    // _state is the enum corresponding to which gamestate this is.
    const GamestateType _state;

    // This is the space that the gamestate's Update() function will be used on.
    // You may want to do that on multiple spaces... 
    // That should be easy & fun to implement. :)
    std::string _LogicalSpace = "Game World";
  protected:
    // These function is only available to the gamestate.
    // This sets the logical space to something of your choosing.
    void SetLogicalSpace(std::string);

    // This functions registers a space to be updated while this gamestate is active.
    inline void RegisterSpace(SpacePtr space)
    {
      _spaces.push_back(space->Name());
    }
    inline void RegisterSpace(std::string name)
    {
      _spaces.push_back(name);
    }
    void DeRegisterSpace(std::string name) 
    {
      auto it = _spaces.begin();
      for (; it != _spaces.end(); ++it)
        if (*it == name)
          break;

      if (it != _spaces.end())
        _spaces.erase(it);

    }
  };

  // Typedef away text so you don't have to type as much!
  typedef std::shared_ptr<Gamestate> GamestatePtr;

} // AlJeEngine
