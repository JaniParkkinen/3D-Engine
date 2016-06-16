#ifndef Engine_EntityManager_hpp
#define Engine_EntityManager_hpp

#include <unordered_map>																							
#include <string>																									
#include <memory>																									

#include <Core\Time.hpp>																							

namespace Engine {
	///Component flags
	#define NONE		0x00000000u
	#define AABB		0x00000001u
	#define CAMERA		0x00000002u
	#define MATERIAL	0x00000004u
	#define RENDERABLE	0x00000008u
	#define SHADER		0x00000010u
	#define TEXTURE		0x00000020u
	#define TRANSFORM	0x00000040u

	///System flags
	#define RENDER		0x00000048u
	#define PHYSICS		0x00000049u

	// COMPONENT
	struct Component {
	public:
		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		size_t GetType( );
	protected:
		size_t _type;

	};

	// ENTITY
	struct Entity {
	public:
		Entity( std::string name ) : _name( name ) { };
		virtual ~Entity( ) { };

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		virtual void Update( DeltaTime deltaTime ) = 0;

		template <typename T> std::shared_ptr<T> AddComponent( std::shared_ptr<Component> component );
		template <typename T> std::shared_ptr<T> GetComponent( size_t flag );
		void Entity::RemoveComponent( size_t flag );

		void SetName( std::string name );
		std::string GetName( );

	protected:
		std::string _name;

		std::unordered_map<size_t, std::shared_ptr<Component>> _components;
		size_t key;

	};

	// ENTITY MANAGER
	class EntityManager {
	public:
		template <typename T> std::shared_ptr<T> AddEntity( std::shared_ptr<Entity> entity );
		template <typename T> std::shared_ptr<T> AddComponent( std::string name, std::shared_ptr<Component> component);

	private:
		std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;
	};

	#include <Core/Managers/EntityManager.inl>
}
#endif
