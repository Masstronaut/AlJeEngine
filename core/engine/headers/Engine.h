/**
 * @author Allan Deutsch
 * @version 0.5
 * @copyright Copyright (C) Allan Deutsch & Jeff Uong. All rights reserved.
 *
 * @brief The Engine class is the core of the game engine.
 *
 */


#pragma once
#include <memory> // Shared pointers for automatic memory management
#include <vector>
#include <unordered_map>
#include <stack>

#include "Gamestate.h"
#include "System.h"
#include "Entity.h"
#include "Space.h"
#include "ArchetypeFactory.h"
#include "Message.h"

#include "../../Gamestates/GamestatesInclude.h"
#include "../../Systems/SystemsInclude.h"

namespace AlJeEngine
{

  struct Engine
  {
    /*!
    * @brief Constructs the Engine and sets the global ENGINE pointer.
    *
    * @par This function will cause the program to exit if the ENGINE pointer is not a nullptr.
    */
    Engine();
    /*!
    * @brief Initializes the Engine
    * @detail This is where the startup operations happen.
    *   Systems are added and initialized, variables are set, and the initial space is created.
    */
    void Init();
    /*!
    * @brief Attempts to safely shut down the Engine.
    * @detail Shuts down all the systems, clears out all the spaces, and shuts down and pops all the gamestates.
    */
    void Shutdown();

    /*!
    * @brief Updates the Engine.
    * @detail Updating happens at multiple levels. 
    * The window handler system (WindowSDL) is updated first. It sends out messages about window changes and input events.
    * The Engine then updates every space that the current gamestate says should be updated.
    * When a Space is updated, it provides each of the systems added to it with a vector of entities that meet the system's registration requirements.
    * The Space then tells the System to update.
    *
    * @param[in] dt The time that elapsed during the last frames update call.
    */
    void Update(float dt);

    /*!
    * @brief Creates a timer and calls Update(dt) repeatedly.
    * @details Each frame is timed so that the elapsed time can be passed on to the next frame. This function automates the update process.
    *
    * @par This function is used when AlJeEngine is not being used by any external libraries.
    *  If you wish to use AlJeEngine inside another project, you can manually call the Update(dt) function as needed.
    */
    void mainLoop();

    /*!
    * @brief Creates a Space in the engine with the specified name.
    *
    * @param[in] name The name that will be used to identify the created space.
    *
    * @return Returns a SpacePtr containing the space that was created by this function.
    */
    SpacePtr CreateSpace(std::string name);

    /*!
    * @brief Gets the Space in the engine with the specified name.
    *
    * @param[in] name The name of the space to retrieve.
    *
    * @return Returns a SpacePtr containing the space with the specified name..
    */
    SpacePtr GetSpace(std::string name);

    /*!
    * @brief Sets the active space in the engine.
    * @par This function will throw an exception if the user is attempting to set the active space to one that doesn't exist.
    *
    * @param[in] name The name of the space to retrieve.
    *
    * @return Returns a SpacePtr containing the space with the specified name.
    */
    SpacePtr SetActiveSpace(std::string name);

    /*!
    * @brief Allows the user to access the current active space.
    *
    * @return Returns a SpacePtr containing the current active space.
    */
    SpacePtr GetActiveSpace();

    /*!
    * @brief Checks if there is an existing space with the specified name.
    *
    * @param[in] name The name being used as an identifier for the space.
    *
    * @return Returns true if a space with the specified name exists and false if it doesn't.
    */
    bool SpaceExists(std::string name);

    /*!
    * @brief Grants access to the Engine's Archetype factory.
    * 
    * @note When the Archetype Factory is used to create an object, it is NOT automatically added to a space.
    * In order for the object to show up in the game in some way, the user must add it to the correct space themself.
    *
    * @par The create function is not exception safe. If you try to create an Archetype using an invalid name,
    * it will throw an exception.
    *
    * @return Returns a reference to the Engine's Archetype Factory.
    */
    ArchetypeFactory& Factory();

    /*!
    * @brief sends a basic message to all systems and the current gamestate.
    *
    * @note One or both of the EntityPtr objects will be empty for some message values.
    * For example, a message about a keypress event will not include any EntityPtr objects.
    * A collision message would include one or two EntityPtr objects, 
    * depending on if the collision was between two objects or one object and the mouse.
    *
    * @param[in] e1 The first entity involved in the message. 
    * nullptr if there are no entities involved with the message.
    *
    * @param[in] e2 The first entity involved in the message. 
    * nullptr if there are no entities involved with the message.
    *
    * @param[in] message The message value to be included in the message.
    */
    void SendMsg(EntityPtr e1, EntityPtr e2, Message::Message message);

    /*!
    * @brief Allows access to the current time delta being used by the Engine.
    * @par This will typically be the time that was elapsed during the previous frames Update(dt) call.
    *
    * @return The time delta being used by the current frame.
    */
    float Getdt() { return dt; }

    /*!
    * @brief Allows access to a system running in the engine via system type.
    *
    * @note This function call can be made much easier using the GETSYS macro defined below in Engine.h
    * The macro takes the system typename (IE GLGraphics) and expands it to fill the function call template parameter and arguments.
    * The macro also automatically includes the preceding ENGINE-> so that you don't have to!
    *
    * @param[in] sysType The type of the system being accessed.
    *
    * @return Returns a shared pointer to the requested system.
    *
    */
    template<typename T>
    std::shared_ptr<T> GetSystem(EnumeratedSystem sysType);

    /*!
    * @brief Signals to the engine that it should stop running.
    */
    void Stop(void) { _running = false;  }

    /*!
    * @brief allows access to the currently active gamestate.
    *
    * @return Returns a GamestatePtr containing the currently active gamestate.
    */
    GamestatePtr CurrentState() const;

    /*!
    * @brief Adds a new gamestate to the top of the gamestate stack.
    *
    * @param[in] gamestate A GamestatePtr object containing an instance of whatever gamestate is being pushed.
    */
    void PushGamestate(GamestatePtr gamestate);

    /*!
    * @brief Tells the current gamestate to shutdown, then pops it off the stack.
    */
    void PopGamestate();

  private:

    std::stack<GamestatePtr> _gamestates;

    float dt;

    std::string _activeSpace;

    typedef std::unordered_map<std::string, SpacePtr> SpaceMap;

     SpaceMap _spaces;

    SystemVec _systems;

    ArchetypeFactory _archetypeFactory;

    bool _running = true;
  };

#define GETSYS( systype ) \
ENGINE->GetSystem<systype>(ES_##systype)

  template <typename T>
  std::shared_ptr<T> Engine::GetSystem(EnumeratedSystem sysType)
  {
    for (auto &it : _systems)
    {
      if (it->_type == sysType)
        return std::static_pointer_cast<T>(it);
    }

    // Throw an error if the system doesn't exist in the engine.
    throw std::range_error("The specified system does not exist.");

  }



}; // AlJeEngine
