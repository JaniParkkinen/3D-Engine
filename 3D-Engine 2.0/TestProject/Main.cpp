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

		Engine::SystemManager::GetInstance( )->AddSystem<Engine::RenderingSystem>( std::make_shared<Engine::RenderingSystem>( &window ) );
		Engine::SystemManager::GetInstance( )->AddSystem<Engine::PhysicsSystem>( std::make_shared<Engine::PhysicsSystem>( ) );

		Engine::Time deltaTime;

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Player" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>("Player", std::make_shared<Engine::Material>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getMaterial()));
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Player", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getShapes( ) ) )->ScaleTexture( 0.1f );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Player", std::make_shared<Engine::Transform>( glm::vec3( 2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Player", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Player", std::make_shared<Engine::Texture>( "Assets/Box.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Player", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Child" ) );
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Material>("Child", std::make_shared<Engine::Material>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getMaterial()));
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Child", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getShapes( ) ) )->ScaleTexture( 0.1f );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Child", std::make_shared<Engine::Transform>( glm::vec3( -2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Child", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Child", std::make_shared<Engine::Texture>( "Assets/Box.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Child", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );

		Engine::EntityManager::GetInstance( )->GetEntity<Player>( "Player" )->SetChild( "Child" );

		glm::vec2 asd;

		while ( window.IsOpen( ) ) {
			deltaTime.Update( );

			if ( mouse.getMouseDown( MK_LBUTTON ) ) {
				asd = mouse.getPosition( );
			} else if ( mouse.getMouse( MK_LBUTTON ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( "Player", TRANSFORM )->Rotate( glm::vec3( -( mouse.getPosition( ) - asd ).y, ( mouse.getPosition( ) - asd ).x, 0.0f ) );
				asd = mouse.getPosition( );
			}

			if ( keyboard.getKey( '1' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( "Player", TRANSFORM )->Rotate( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '2' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( "Player", TRANSFORM )->Rotate( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			}
			if ( keyboard.getKey( '3' ) ) {
				Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( "Player", TRANSFORM )->Rotate( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			}

			if ( keyboard.getKey( VK_ESCAPE ) ) {
				exit( 0 );
			}

			Engine::SystemManager::GetInstance( )->Update( deltaTime.GetDeltaTime( ) );
			keyboard.update( );
			mouse.update( );
			window.getMessage( );
		};

		exit( 0 );
	} catch ( int i ) {
		return i;
	} catch ( ... ) {
		return -1;
	};
};