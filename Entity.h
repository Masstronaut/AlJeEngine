#include <string>
#include "Component.h"

struct Entity
{
  /**
   * @brief Adds a component to the entity by pointer.
   * 
   * @param component Pointer to the component being added to the entity.
   */
  void AddComponent                          ( Component *component   );

  /**
   * @brief Removes a component from the entity.
   * 
   * @param ec The type of component to remove from the entity.
   */
  void RemoveComponent                       ( EnumeratedComponent ec );

  /**
   * @brief Checks if the entity has a specific type of component.
   * 
   * @param ec The type of component to check for.
   * @return Returns true if the entity has the specified component type, false otherwise.
   */
  bool HasComponent                          ( EnumeratedComponent ec );


#define GET_COMPONENT( type ) \
  GetComponent<type>(EC_##type)

  template <typename T>
  T*   GetComponent                          ( EnumeratedComponent  );

  std::unique_ptr<Component> * _components[EC_Max];
  std::string _name;
};
