namespace Engine {
// COMPONENT

// ENTITY
	template <typename T> std::shared_ptr<T> Entity::AddComponent( std::shared_ptr<Component> component ) {
		if ( _components.find( component->GetType( ) ) == _components.end( ) ) {
			_components.insert( std::make_pair( component->GetType( ), component ) );
			key = key | component->GetType( );
		}
	} // AddComponent

	template <typename T> std::shared_ptr<T> Entity::GetComponent( size_t flag ) {
		std::unordered_map<size_t, std::shared_ptr<Component>>::iterator it = _components.find( flag );
		if ( it != _components.end( ) ) {
			return std::static_pointer_cast< T >( it->second );
		}
		return nullptr;
	} // GetComponent



	// ENTITY MANAGER
	template <typename T> std::shared_ptr<T> EntityManager::AddEntity( std::shared_ptr<Entity> entity ) {
		if ( _entities.find( entity->GetName( ) ) == _entities.end( ) ) {
			_entities.insert( std::make_pair( entity->GetName( ), entity ) );
			return std::static_pointer_cast< T >( entity );
		}
		return nullptr;
	} // AddEntity

	template <typename T> std::shared_ptr<T> EntityManager::AddComponent( std::string name, std::shared_ptr<Component> component ) {
		std::unordered_map<std::string, std::shared_ptr<Entity>>::iterator it = _entities.find( name );
		if ( it != _entities.end( ) ) {
			it->second->AddComponent<T>( component );
			return std::static_pointer_cast< T >( component );
		}
		return nullptr;
	} // AddEntity
}
