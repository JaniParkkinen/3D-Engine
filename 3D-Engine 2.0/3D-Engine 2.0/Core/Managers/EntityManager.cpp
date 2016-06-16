#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	// COMPONENT
	size_t Component::GetType( ) {
		return _type;
	} // GetType

	// ENTITY
	void Entity::SetName( std::string name ) {
		_name = name;
	} // SetName

	std::string Entity::GetName( ) {
		return _name;
	} // GetName

	void Entity::RemoveComponent( size_t flag ) {
		if ( _components.find( flag ) != _components.end( ) ) {
			_components.erase( flag );
		}
	} // RemoveComponent


}
