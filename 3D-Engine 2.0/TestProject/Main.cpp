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

int main( ) {
	try {
		window.createWindow( "3D-Engine", glm::vec2( 800.0f, 600.0f ), glm::vec2( 0.0f, 0.0f ), "", "", ENGINE_WINDOWED, WndProc );
		window.InitOpenGL( );

		Engine::SystemManager::GetInstance( )->AddSystem<Engine::RenderingSystem>( std::make_shared<Engine::RenderingSystem>( &window ) );

		Engine::Time deltaTime;

		while ( window.IsOpen( ) ) {
			deltaTime.Update( );

			if ( keyboard.getKeyDown( '1' ) ) {
				Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Test.txt" );
			}
			if ( keyboard.getKeyDown( '2' ) ) {
				Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Test.png" );
			}
			if ( keyboard.getKeyDown( '3' ) ) {
				Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Test.obj" );
			}
			if ( keyboard.getKey( VK_ESCAPE ) ) {
				exit( 0 );
			}

			Engine::SystemManager::GetInstance( )->Update( deltaTime.GetDeltaTime() );
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