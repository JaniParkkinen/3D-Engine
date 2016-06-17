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

	void SystemManager::PauseSystem( size_t flag ) {
		_systems.find( flag )->second->Pause( );
	} // PauseSystem

	void SystemManager::ResumeSystem( size_t flag ) {
		_systems.find( flag )->second->Resume( );
	} // ResumeSystem

	void SystemManager::Update( DeltaTime deltaTime ) {
		for ( std::pair<size_t, std::shared_ptr<System>> system : _systems ) {
			system.second->Update( deltaTime );
		}
	} // Update
}
