#ifndef Player_hpp
#define Player_hpp

struct Player : Engine::Entity {
	Player( std::string name );
	virtual ~Player( );
	virtual void Init( ) override;
	virtual void Cleanup( ) override;
	virtual void Update( Engine::DeltaTime deltaTime ) override;
}; 

#endif
