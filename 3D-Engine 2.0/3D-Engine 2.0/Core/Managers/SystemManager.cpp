#include <Core/Managers/SystemManager.hpp>

namespace Engine {
	size_t System::GetFlag( ) {
		return _flag;
	} // GetFlag

	void SystemManager::RemoveSystem( size_t flag ) {
		if ( _systems.find( flag ) != _systems.end( ) ) {
			_systems.erase( flag );
		}
	} // RemoveSystem
}
