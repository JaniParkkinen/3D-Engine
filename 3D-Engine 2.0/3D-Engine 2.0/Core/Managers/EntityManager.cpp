#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	// COMPONENT
	void Component::SetOwner( std::shared_ptr<Entity> owner ) {
		_owner = owner;
	}

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

	size_t const & Entity::GetKey( ) {
		return key;
	} // GetKey

	std::vector < std::shared_ptr<Entity>> Entity::GetChildren( ) {
		return _children;
	} // GetChildren

	void Entity::RemoveComponent( size_t flag ) {
		if ( _components.find( flag ) != _components.end( ) ) {
			_components.erase( flag );
		}
	} // RemoveComponent

	void Entity::RemoveComponents( ) {
		_components.clear( );
	} // RemoveComponents

	void Entity::SetChild( std::string name ) {
		_children.push_back( EntityManager::GetInstance( )->GetEntity<Entity>( name ) );
	}

	// ENTITY MANAGER
	std::vector<std::shared_ptr<Entity>> EntityManager::GetEntities( size_t flag ) {
		std::vector<std::shared_ptr<Entity>> entities;
		for ( std::pair<std::string, std::shared_ptr<Entity>> entity : _entities ) {
			if ( ( entity.second->GetKey( ) & flag ) == flag ) {
				entities.push_back( entity.second );
			}
		}
		return entities;
	} // GetEntities

	std::vector<std::shared_ptr<Entity>> EntityManager::GetEntities( ) {
		std::vector<std::shared_ptr<Entity>> entities;
		for ( std::pair<std::string, std::shared_ptr<Entity>> entity : _entities ) {
			entities.push_back( entity.second );
		}
		return entities;
	} // GetEntities

	void EntityManager::RemoveEntity( std::string name ) {
		std::unordered_map<std::string, std::shared_ptr<Entity>>::iterator it = _entities.find( name );
		if ( it != _entities.end( ) ) {
			it->second->RemoveComponents( );
			it->second->Cleanup( );
			_entities.erase( name );
		}
	} // RemoveEntity

	void EntityManager::RemoveEntities( ) {
		for ( std::pair<std::string, std::shared_ptr<Entity>> entity : _entities ) {
			entity.second->RemoveComponents( );
		}
		_entities.clear( );
	} // RemoveEntities

	void EntityManager::RemoveComponent( std::string name, size_t flag ) {
		std::unordered_map<std::string, std::shared_ptr<Entity>>::iterator it = _entities.find( name );
		if ( it != _entities.end( ) ) {
			it->second->RemoveComponent( flag );
		}
	} // RemoveComponent

	void EntityManager::Update( DeltaTime deltaTime ) {
		for ( std::pair<std::string, std::shared_ptr<Entity>> entity : _entities ) {
			entity.second->Update( deltaTime );
		}
	} // Update
}
