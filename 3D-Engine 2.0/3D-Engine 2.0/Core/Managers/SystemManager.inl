template <typename T> std::shared_ptr<T> SystemManager::AddSystem( std::shared_ptr<System> system ) {
	if ( _systems.find( system->GetFlag( ) ) == _entities.end( ) ) {
		_systems.insert( std::make_pair( system->GetFlag( ), system ) );
		return std::static_pointer_cast< T >( system );
	}
	return nullptr;
} // AddSystem

template <typename T> std::shared_ptr<T> SystemManager::GetSystem( size_t flag ) {
	std::unordered_map<size_t, std::shared_ptr<System>>::iterator it = _systems.find( flag );
	if ( it != _systems.end( ) ) {
		return std::static_pointer_cast< T >( it->second );
	}
	return nullptr;
} // GetSystem
