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
  /*!
  * @brief These are used to keep track of the current gamestate,
  * and to tell gamestates which state was the previous state.
  */
  enum GamestateType
  {
    GS_MainMenu,
    GS_PauseMenu,
    GS_TestDemo,
    GS_Asteroids,
  };

  class Gamestate : public System
  {

  public:
    /*!
    * @brief Constructs a base gamestate object.
    * 
    * @param name The gamestate's name.
    * @param GST the GamestateType enum value corresponding to this gamestate's type.
    */
    Gamestate(std::string name, GamestateType GST)
      : System(name, ES_Gamestate), _state(GST)
    {
    }

    /*!
    * @brief this virtual destructor is required to ensure proper cleanup of derived gamestate classes.
    */
    virtual ~Gamestate() {}

    /*!
    * @brief This is a pure virtual function defining the interface of a Gamestate.
    * This function will be called once by the Engine when this gamestate is created.
    * @note This function must be implemented in any derived classes.
    */
    virtual void Init() = 0;

    /*!
    * @brief This is a pure virtual function defining the interface of a Gamestate.
    * This function will be called once per frame while the gamestate is active.
    * @note This function must be implemented in any derived classes.
    */
    virtual void Update(float) = 0;

    /*!
    * @brief This is a pure virtual function defining the interface of a Gamestate.
    * This function will be called once by the Engine when this gamestate is being destroyed.
    * @note This function must be implemented in any derived classes.
    */
    virtual void Shutdown() = 0;

    /*!
    * @brief this function is called when this gamestate becomes active due to a gamestate on top of it being popped.
    *
    * @param GST The GamestateType value of the gamestate that was popped.
    */
    virtual void PoppedTo(GamestateType GST) {}

    /*!
    * @brief Exposes the type of gamestate that this object is.
    *
    * @return the GamestateType of this gamestate.
    */
    inline GamestateType State() const 
    { 
      return _state; 
    }

    /*!
    * @brief Exposes the spaces that will be updated while this gamestate is active.
    *
    * @return Returns a vector of strings, where each string is the name of a space.
    */
    inline const std::vector<std::string>& GetSpaces() const
    {
      return _spaces;
    }

    /*!
    * @brief Exposes the name of the space that this gamestate's logic will be used with.
    * @note Only one space will have the gamestate's logic applied. That is the logical space.
    * 
    * @return Returns the name of the logical space.
    */
    const std::string& GetLogicalSpace() 
    { 
      return _LogicalSpace; 
    }

    /*!
    * @brief allows the user to check if a space with a specified name is used by this gamestate.
    *
    * @param space The name corresponding to the space that is being checked.
    *
    * @return Returns true if the space is used by this gamestate, false otherwise.
    */
    bool CheckSpaceActive(std::string space);

  private:
    // Default construction is not allowed. All gamestates MUST have a type and name.
    Gamestate() = delete;

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

    // These functions registers a space to be updated while this gamestate is active.
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
