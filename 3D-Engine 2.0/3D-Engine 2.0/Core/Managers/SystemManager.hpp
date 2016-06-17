#ifndef Engine_SystemManager_hpp
#define Engine_SystemManager_hpp

#include <vector>
#include <memory>
#include <unordered_map>

#include <Core/Time.hpp>

namespace Engine {
	///System flags
	#define NONE		0x00000000u
	#define RENDER		0x00000048u
	#define PHYSICS		0x00000049u

	struct System {
		System( size_t flag = NONE ) : _paused( false ), _flag(flag) { };
		virtual ~System( ) { };

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		virtual void Pause( ) = 0;
		virtual void Resume( ) = 0;

		virtual void Update( DeltaTime deltaTime ) = 0;

		size_t GetFlag( );

	protected:
		bool _paused;
		size_t _flag;
	};

	class SystemManager {
	public:
		static SystemManager* GetInstance( ) {
			static SystemManager systemManager;
			return &systemManager;
		}

		template <typename T> std::shared_ptr<T> AddSystem( std::shared_ptr<System> system );
		template <typename T> std::shared_ptr<T> GetSystem( size_t flag );

		void RemoveSystem( size_t flag );

		void PauseSystem( size_t flag );
		void ResumeSystem( size_t flag );

		void Update( DeltaTime deltaTime );

	private:
		SystemManager( ) { }
		SystemManager( SystemManager const & );
		void operator=( SystemManager const & );

		std::unordered_map<size_t, std::shared_ptr<System>> _systems;
	};

	#include <Core/Managers/SystemManager.inl>
}
#endif
