#include <Core/Managers/SystemManager.hpp>

namespace Engine {
	inline void SystemManager::Clear( ) {
		while ( !_systems.empty( ) ) {
			_systems.back( )->Cleanup( );
			_systems.pop_back( );
		};
	};

	inline void SystemManager::Update( DeltaTime deltaTime ) {
		for ( auto it : _systems ) {
			it->Update( deltaTime );
		};
	};
};