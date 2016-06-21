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

	// COMPONENT
	struct Component {
	public:
		Component( size_t type = NONE ) : _type( type ) { }
		virtual ~Component( ) { }

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		void SetOwner( std::shared_ptr<struct Entity> owner );
		size_t GetType( );
	protected:
		size_t _type;
		std::shared_ptr<Entity> _owner;
	};

	// ENTITY
	struct Entity : std::enable_shared_from_this<Entity> {
	public:
		Entity( std::string name ) : _name( name ), key(NONE) { }
		virtual ~Entity( ) { }

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		virtual void Update( DeltaTime deltaTime ) = 0;

		template <typename T> std::shared_ptr<T> AddComponent( std::shared_ptr<Component> component );

		template <typename T> std::shared_ptr<T> GetComponent( size_t flag );

		void Entity::RemoveComponent( size_t flag );
		void Entity::RemoveComponents( );

		void SetName( std::string name );
		std::string GetName( );
		std::vector<std::shared_ptr<Entity>> GetChildren( );
		size_t const & GetKey( );
		void SetChild( std::string name );
	protected:
		std::string _name;

		std::vector<std::shared_ptr<Entity>> _children;
		std::unordered_map<size_t, std::shared_ptr<Component>> _components;
		size_t key;

	};

	// ENTITY MANAGER
	class EntityManager {
	public:
		static EntityManager* GetInstance( ) {
			static EntityManager entityManager;
			return &entityManager;
		}

		template <typename T> std::shared_ptr<T> AddEntity( std::shared_ptr<Entity> entity );
		template <typename T> std::shared_ptr<T> AddComponent( std::string name, std::shared_ptr<Component> component );

		template <typename T> std::shared_ptr<T> GetEntity( std::string name );
		template <typename T> std::shared_ptr<T> GetComponent( std::string name, size_t flag );

		std::vector<std::shared_ptr<Entity>> GetEntities( );

		void RemoveEntities( );
		void RemoveEntity( std::string name );
		void RemoveComponent( std::string name, size_t flag );

		void Update( DeltaTime deltaTime );
	private:
		EntityManager( ) { }

		EntityManager( EntityManager const & ) { }
		void operator=( EntityManager const & ) { }

		std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;
	};

	#include <Core/Managers/EntityManager.inl>
}
#endif
