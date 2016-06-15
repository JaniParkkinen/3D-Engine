#ifndef Engine_EntityManager_hpp
#define Engine_EntityManager_hpp

#include <unordered_map>																							
#include <string>																									
#include <memory>																									

#include <Core\Time.hpp>																							

namespace Engine {
///Component flags
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

	typedef struct Component {
		Component( ) : _owner( nullptr ) { };
		virtual ~Component( ) { };

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		virtual void Update( DeltaTime deltaTime ) = 0;

		std::shared_ptr<struct Entity> getOwner( ) { return _owner; };

	protected:
		std::shared_ptr<struct Entity> _owner;
	} Component;

	typedef struct Entity : std::enable_shared_from_this<Entity> {
		Entity( ) : _parent( nullptr ) { };
		virtual ~Entity( ) { };

		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;

		virtual void Update( DeltaTime deltaTime ) = 0;

		template <typename T> std::shared_ptr<T> AddChild( std::shared_ptr<T> child );
		template <typename T, typename ...args> std::shared_ptr<T> AddComponent( args&&... param );
		template <typename T> void RemoveComponent( );

		template <typename T> std::shared_ptr<T> GetComponent( );

		void RemoveChild( const char* name );
		void SetName( const char* name ) { _name = name; };

		std::string GetName( void );
		std::shared_ptr<Entity> GetParent( void );
		std::shared_ptr<Entity> GetChild( const char* name );
		std::vector<std::shared_ptr<Entity>> GetChildren( void );
		std::vector<std::shared_ptr<Component>> GetComponents( );

	protected:
		std::string _name;
		std::shared_ptr<Entity> _parent;
		std::vector<std::shared_ptr<Entity>> _children;
		std::vector<std::shared_ptr<Component>> _components;
	} Entity;

	typedef class EntityManager {
	public:
		static EntityManager* GetInstance( ) {
			static EntityManager entityManager;
			return &entityManager;
		};

		std::shared_ptr<Entity> AddEntity( std::string name, std::shared_ptr<Entity> entity );
		void RemoveEntity( std::string name );

		void Update( DeltaTime deltaTime );

		void Clear( );

		std::shared_ptr<Entity> GetEntity( std::string name );
		std::vector<std::shared_ptr<Entity>> GetEntities( );

		template <typename T, typename ...args> std::shared_ptr<T> AddComponent( std::string name, args&&... param );

		template <typename T> std::vector<std::shared_ptr<T>> GetComponents( );
		template <typename T> std::vector<std::shared_ptr<T>> GetComponents( std::string name );

		std::vector<std::shared_ptr<Component>> GetComponents( );
		std::vector<std::shared_ptr<Component>> GetComponents( std::string name );
	private:
		std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;

		EntityManager( ) { };
		~EntityManager( ) { Clear( ); };

		EntityManager( EntityManager const& ) { };
		void operator=( EntityManager const& ) { };
	} EntityManager; // EntityManager

	template <typename T> std::shared_ptr<T> Entity::AddChild( std::shared_ptr<T> child ) {
		_children.push_back( child );
		child->_parent = std::shared_ptr<Entity>( shared_from_this( ) );
		return child;
	} // AddChild

	template <typename T, typename ...args> std::shared_ptr<T> Entity::AddComponent( args&&... param ) {
		for ( auto it : _components ) {
			if ( std::dynamic_pointer_cast< T >( it ) != nullptr ) { return std::shared_ptr<T>( ); }
		}
		_components.push_back( std::make_shared<T>( param... ) );
		_components.back( )->_owner = this->shared_from_this( );
		_components.back( )->Init( );
		return std::dynamic_pointer_cast< T >( _components.back( ) );
	} // AddComponent

	template <typename T> void Entity::RemoveComponent( ) {
		//Will be simplified with bitfield operations
		for ( auto it = _components.begin( ); it != _components.end( );) {
			if ( std::dynamic_pointer_cast< T >( *it ) != nullptr ) {
				it->get( )->Cleanup( );
				it = _components.erase( it );
			} else {
				it++;
			}
		}
	} // RemoveComponent

	template <typename T> std::shared_ptr<T> Entity::GetComponent( ) {
		for ( auto it : _components ) {
			if ( std::dynamic_pointer_cast< T >( it ) != nullptr ) {
				return std::static_pointer_cast< T >( it );
			}
		}
		return std::shared_ptr<T>( );
	} // GetComponent

	template <typename T, typename ...args> std::shared_ptr<T> EntityManager::AddComponent( std::string name, args&&... param ) {
		return GetEntity( name )->AddComponent<T>( param... );
	} // AddComponent

	template <typename T> std::vector<std::shared_ptr<T>> EntityManager::GetComponents( ) {
		std::vector<std::shared_ptr<T>> tempVec;
		for ( auto it : _entities ) {
			tempVec.push_back( std::static_pointer_cast< T >( it.second->GetComponent<T>( ) ) );
		}
		return tempVec;
	} // GetComponents

	template <typename T> std::vector<std::shared_ptr<T>> EntityManager::GetComponents( std::string name ) {
		std::vector<std::shared_ptr<T>> tempCompVec;
		tempCompVec.push_back( std::static_pointer_cast< T >( _entities.find( name )->second->GetComponent<T>( ) ) );
		return tempCompVec;
	} // GetComponents
}
#endif
