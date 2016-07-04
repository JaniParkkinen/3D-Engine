#include <iostream>
#include <Windows.h>
#include <Core/3DEngine.hpp>

Engine::Window window;
Engine::Keyboard keyboard;
Engine::Mouse mouse;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	switch ( msg ) {
		case WM_KEYDOWN:
			keyboard.keyDown( wParam );
			break;
		case WM_KEYUP:
			keyboard.keyUp( wParam );
			break;
		case WM_MOUSEMOVE:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_LBUTTONDOWN:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_LBUTTONUP:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_MBUTTONDOWN:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_MBUTTONUP:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_RBUTTONDOWN:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_RBUTTONUP:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_MOUSEWHEEL:
			mouse.mouseWheelIn( GET_WHEEL_DELTA_WPARAM( wParam ) );
			break;
		case WM_XBUTTONDOWN:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_XBUTTONUP:
			mouse.mouseEvent( GET_KEYSTATE_WPARAM( wParam ), glm::vec2( LOWORD( lParam ), HIWORD( lParam ) ) );
			break;
		case WM_SETFOCUS:
			break;
		case WM_KILLFOCUS:
			break;
		case WM_SIZE:
			window.Resize( );
			break;
		case WM_CLOSE:
			DestroyWindow( hwnd );
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		default:
			return DefWindowProc( hwnd, msg, wParam, lParam );
	}
	return 0;
}

struct Player : Engine::Entity {
	Player( std::string name ) : Entity( name ) { };
	virtual ~Player( ) { };
	virtual void Init( ) override { };
	virtual void Cleanup( ) override { };
	virtual void Update( Engine::DeltaTime deltaTime ) override { };
};

int main( ) {
	try {
		window.createWindow( "3D-Engine", glm::vec2( 800.0f, 600.0f ), glm::vec2( 0.0f, 0.0f ), "", "", ENGINE_BORDERLESS, WndProc );
		window.InitOpenGL( );

		Engine::SystemManager::GetInstance( )->AddSystem<Engine::PhysicsSystem>( std::make_shared<Engine::PhysicsSystem>( ) );
		Engine::SystemManager::GetInstance( )->AddSystem<Engine::RenderingSystem>( std::make_shared<Engine::RenderingSystem>( &window ) );


		Engine::Time deltaTime;

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Player" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( "Player", std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getMaterial( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Player", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Teapot.obj" )->getShapes( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Player", std::make_shared<Engine::Transform>( glm::vec3( 0.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) * glm::vec3( 0.01f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Player", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Player", std::make_shared<Engine::Texture>( "Assets/Test.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Player", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Physics>( "Player", std::make_shared<Engine::Physics>( ) );

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Parent" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Parent", std::make_shared<Engine::Transform>( glm::vec3( 0.0f, 0.0f, 5.0f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Physics>( "Parent", std::make_shared<Engine::Physics>( ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::DirectionalLight>( "Parent", std::make_shared<Engine::DirectionalLight>( glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), 0.1f, 0.1f ) );

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Child1" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( "Child1", std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getMaterial( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Child1", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Child1", std::make_shared<Engine::Transform>( glm::vec3( -2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Child1", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Child1", std::make_shared<Engine::Texture>( "Assets/Box.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Child1", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::PointLight>( "Child1", std::make_shared<Engine::PointLight>( glm::vec3( 1.0f, 0.5f, 0.25f ), 0, glm::vec3( 0.0f, 1.0f, 0.0f ), 1.0f, 1.0f ) );

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Child2" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( "Child2", std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getMaterial( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Child2", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Child2", std::make_shared<Engine::Transform>( glm::vec3( 2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Child2", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Child2", std::make_shared<Engine::Texture>( "Assets/Box.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Child2", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::SpotLight>( "Child2", std::make_shared<Engine::SpotLight>( glm::vec3( 0.0f, 0.0f, 1.0f ), 0.99f, 0, glm::vec3( 1.0f, 0.025f, 0.025f ), glm::vec3( 0.0f, 1.0f, 0.0f ), 1.0f, 1.0f, SPOT_LIGHT ) );

		Engine::EntityManager::GetInstance( )->GetEntity<Player>( "Parent" )->SetChild( "Child1" );
		Engine::EntityManager::GetInstance( )->GetEntity<Player>( "Parent" )->SetChild( "Child2" );

		while ( window.IsOpen( ) ) {
			deltaTime.Update( );

			if ( keyboard.getKey( '1' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '2' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '3' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			}
			if ( keyboard.getKey( '4' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '5' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '6' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			}
			if ( keyboard.getKey( 'W' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			}
			if ( keyboard.getKey( 'S' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 0.0f, -1.0f ) );
			}
			if ( keyboard.getKey( 'A' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			}
			if ( keyboard.getKey( 'D' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( -1.0f, 0.0f, 0.0f ) );
			}
			if ( keyboard.getKey( 'E' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			}
			if ( keyboard.getKey( 'Q' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, -1.0f, 0.0f ) );
			}
			if ( keyboard.getKey( VK_SPACE ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->SetAngularVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
			}

			if ( keyboard.getKey( VK_ESCAPE ) ) {
				throw ( 0 );
			}

			Engine::SystemManager::GetInstance( )->Update( deltaTime.GetDeltaTime( ) );
			keyboard.update( );
			mouse.update( );
			window.getMessage( );
		};

		throw ( 0 );
	} catch ( int i ) {
		return i;
	} catch ( ... ) {
		return -1;
	}
}
