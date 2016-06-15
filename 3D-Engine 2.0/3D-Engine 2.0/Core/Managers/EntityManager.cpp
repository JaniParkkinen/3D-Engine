#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	//ENTITY
	void Entity::RemoveChild( const char* name ) {
		for ( std::shared_ptr<Entity> entity : _children ) {
			if ( entity->GetName( ) == name ) {
				entity.reset( );
			}
		}
	} // RemoveChild

	std::vector<std::shared_ptr<Component>> Entity::GetComponents( ) {
		return _components;
	} // GetComponents

	std::string Entity::GetName( ) {
		return _name;
	} // GetName

	std::shared_ptr<Entity> Entity::GetParent( ) {
		return _parent;
	}

	std::shared_ptr<Entity> Entity::GetChild( const char* name ) {
		for ( std::shared_ptr<Entity> entity : _children ) {
			if ( entity->GetName( ) == name ) {
				return entity;
			}
		}
	} // GetChild

	std::vector<std::shared_ptr<Entity>> Entity::GetChildren( ) {
		return _children;
	} // GetChildren

	//ENTITY MANAGER
	std::shared_ptr<Entity> EntityManager::AddEntity( std::string name, std::shared_ptr<Entity> entity ) {
		_entities.insert( std::make_pair( name, entity ) );
		entity->SetName( name.c_str( ) );
		entity->Init( );
		return entity;
	} // AddEntity

	void EntityManager::RemoveEntity( std::string name ) {
		_entities.find( name )->second->Cleanup( );
		_entities.erase( name );
	} // RemoveEntity

	void EntityManager::Update( DeltaTime deltaTime ) {
		for ( auto it : _entities ) {
			it.second->Update( deltaTime );
		}
	} // Update

	void EntityManager::Clear( ) {
		while ( !_entities.empty( ) ) {
			_entities.begin( )->second->Cleanup( );
			_entities.erase( _entities.begin( ) );
		}
	} // Clear

	std::shared_ptr<Entity> EntityManager::GetEntity( std::string name ) {
		return _entities.find( name )->second;
	} // GetEntity

	std::vector<std::shared_ptr<Entity>> EntityManager::GetEntities( ) {
		std::vector<std::shared_ptr<Entity>> temp;
		for ( auto it : _entities ) {
			temp.push_back( it.second );
		}
		return temp;
	} // GetEntities

	std::vector<std::shared_ptr<Component>> EntityManager::GetComponents( ) {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		for ( auto it : _entities ) {
			std::vector<std::shared_ptr<Component>> temp = it.second->GetComponents( );
			tempCompVec.insert( tempCompVec.end( ), temp.begin( ), temp.end( ) );
		}
		return tempCompVec;
	} // GetComponents

	std::vector<std::shared_ptr<Component>> EntityManager::GetComponents( std::string name ) {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		std::vector<std::shared_ptr<Component>> temp = _entities.find( name )->second->GetComponents( );
		tempCompVec.insert( tempCompVec.end( ), temp.begin( ), temp.end( ) );
		return tempCompVec;
	} // GetComponents
}
