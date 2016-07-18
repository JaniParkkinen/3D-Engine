#include <Entities/Player.hpp>

Player::Player( std::string name ) : Entity( name ) {

}

Player::~Player( ) {

}

void Player::Init( ) {
	Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( _name ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( _name, std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getMaterial( ) ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( _name, std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( _name, std::make_shared<Engine::Transform>( glm::vec3( 0.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) * glm::vec3( 0.5f ) ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( _name, std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( _name, std::make_shared<Engine::Texture>( "Assets/Test.png" ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( _name, std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
	Engine::EntityManager::GetInstance( )->AddComponent<Engine::Physics>( _name, std::make_shared<Engine::Physics>( ) );
}

void Player::Cleanup( ) {

}

void Player::Update( Engine::DeltaTime deltaTime ) {

}
