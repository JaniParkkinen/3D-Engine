#include <Core/Managers/SystemManager.hpp>

namespace Engine {
	size_t System::GetFlag( ) {
		return _flag;
	} // GetFlag

	void SystemManager::RemoveSystem( size_t flag ) {
		std::unordered_map<size_t, std::shared_ptr<System>>::iterator it = _systems.find( flag );
		if (it != _systems.end( ) ) {
			it->second->Cleanup( );
			_systems.erase( flag );
		}
	} // RemoveSystem
}
