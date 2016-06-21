// COMPONENT

// ENTITY
template <typename T> std::shared_ptr<T> Entity::AddComponent( std::shared_ptr<Component> component ) {
	if ( _components.find( component->GetType( ) ) == _components.end( ) ) {
		_components.insert( std::make_pair( component->GetType( ), component ) );
		component->SetOwner( shared_from_this( ) );
		key = key | component->GetType( );
		return std::static_pointer_cast< T >( component );
	}
	return nullptr;
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
		return it->second->AddComponent<T>( component );
	}
	return nullptr;
} // AddComponent

template <typename T> std::shared_ptr<T> EntityManager::GetEntity( std::string name ) {
	std::unordered_map<std::string, std::shared_ptr<Entity>>::iterator it = _entities.find( name );
	if ( it != _entities.end( ) ) {
		return std::static_pointer_cast< T >( it->second );
	}
	return nullptr;
} // GetEntity

template <typename T> std::shared_ptr<T> EntityManager::GetComponent( std::string name, size_t flag ) {
	std::unordered_map<std::string, std::shared_ptr<Entity>>::iterator it = _entities.find( name );
	if ( it != _entities.end( ) ) {
		return it->second->GetComponent<T>( flag );
	}
	return nullptr;
} // GetComponent
