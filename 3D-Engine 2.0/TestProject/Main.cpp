#include <Core/3DEngine.hpp>

Engine::Window window;
Engine::Keyboard keyboard;
Engine::Mouse mouse;

struct Camera : Engine::Entity {
public:
	Camera( std::string name ) : Entity( name ) { }
	virtual ~Camera( ) { }
	virtual void Init( ) override {
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>(_name, std::make_shared<Engine::Transform>( Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( _name.substr( 0, _name.find( '_' ) ), TRANSFORM )->GetPosition( ) - glm::vec3( 0.0f, -1.5f, 5.0f ) ) );
		Engine::SystemManager::GetInstance( )->GetSystem<Engine::RenderingSystem>( RENDER )->SetActiveCamera( Engine::EntityManager::GetInstance( )->AddComponent<Engine::Camera>( _name, std::make_shared <Engine::Camera>( glm::vec3( 0.0f, 0.0f, 0.0f ) ) ) );
	}
	virtual void Cleanup( ) override { }
	virtual void Update( Engine::DeltaTime deltaTime ) override { }
private:
};

struct Player : Engine::Entity {
public:
	Player( std::string name ) : Entity( name ) { }
	virtual ~Player( ) { }
	virtual void Init( ) override {
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( _name, std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getMaterial( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( _name, std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( _name, std::make_shared<Engine::Transform>( glm::vec3( 0.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) * glm::vec3( 0.5f ) ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( _name, std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( _name, std::make_shared<Engine::Texture>( "Assets/Box.png" ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( _name, std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::Physics>( _name, std::make_shared<Engine::Physics>( ) );
		Engine::EntityManager::GetInstance( )->AddComponent<Engine::DirectionalLight>( _name, std::make_shared<Engine::DirectionalLight>( glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ), 0, 0.75f, 0.5f ) );

		std::string name = _name + "_camera";
		Engine::EntityManager::GetInstance( )->AddEntity<Camera>( std::make_shared<Camera>( name ) );
		
		SetChild( name );
	}
	virtual void Cleanup( ) override { }
	virtual void Update( Engine::DeltaTime deltaTime ) override {
		if ( keyboard.getKey( 'W' ) ) {
			//Move forward
			Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( Engine::EntityManager::GetInstance( )->GetComponent<Engine::Transform>( _name, TRANSFORM )->GetRotationCam( ) );
		}
		if ( keyboard.getKey( 'S' ) ) {
			//Move backward
			Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 0.0f, -1.0f ) );
		}
		if ( keyboard.getKey( 'A' ) ) {
			//Turn left
			Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
		}
		if ( keyboard.getKey( 'D' ) ) {
			//Turn right
			Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, -1.0f, 0.0f ) );
		}
		if ( keyboard.getKey( 'E' ) ) {
			//Use/interact
		}
		if ( keyboard.getKey( VK_SPACE ) ) {
			//Jump
			Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, -1.0f, 0.0f ) );
		}
	}
private:
};

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

int main( ) {
	try {
		window.createWindow( "3D-Engine", glm::vec2( 800.0f, 600.0f ), glm::vec2( 0.0f, 0.0f ), "", "", ENGINE_BORDERLESS, WndProc );
		window.InitOpenGL( );

		Engine::SystemManager::GetInstance( )->AddSystem<Engine::PhysicsSystem>( std::make_shared<Engine::PhysicsSystem>( ) );
		Engine::SystemManager::GetInstance( )->AddSystem<Engine::RenderingSystem>( std::make_shared<Engine::RenderingSystem>( &window ) );

		Engine::Time deltaTime;

		Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Player" ) );

		while ( window.IsOpen( ) ) {
			deltaTime.Update( );

			if ( keyboard.getKey( VK_ESCAPE ) ) {
				throw ( 0 );
			}

			Engine::EntityManager::GetInstance( )->Update( deltaTime.GetDeltaTime( ) );
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
