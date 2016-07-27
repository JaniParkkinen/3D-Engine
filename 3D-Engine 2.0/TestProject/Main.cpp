#include <iostream>
#include <Windows.h>

#include <Core/3DEngine.hpp>
//#include <Entities/Player.hpp>

Engine::Window window;
Engine::Keyboard keyboard;
Engine::Mouse mouse;

struct Exit : Engine::Entity
{
public:
	Exit(std::string name, glm::vec3 pos) : Entity(name){
		exitPos = pos;
	}
	virtual ~Exit() {}
	virtual void Init() override{
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Material>(_name, std::make_shared<Engine::Material>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getMaterial()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Render>(_name, std::make_shared<Engine::Render>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getShapes()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Transform>(_name, std::make_shared<Engine::Transform>(exitPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.1f, 0.8f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Texture>(_name, std::make_shared<Engine::Texture>("Assets/Normal.png"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Shader>(_name, std::make_shared<Engine::Shader>("Assets/Test.vs", "Assets/Test.fs"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::AxisAlignedBoundingBox>(_name, std::make_shared<Engine::AxisAlignedBoundingBox>());
		Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>(_name, std::make_shared<Engine::PointLight>(glm::vec3(0.0f, 0.1f, 0.1f), 4/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));
	}

	virtual void Cleanup() override{}
	virtual void Update(Engine::DeltaTime deltaTime) override {}
private:
	glm::vec3 exitPos;
};

struct Point : Engine::Entity
{
public:
	Point(std::string name, glm::vec3 pos) : Entity(name) {
		pointPos = pos;
	}
	virtual ~Point() {}
	virtual void Init() override {

		Engine::EntityManager::GetInstance()->AddComponent<Engine::Material>(_name, std::make_shared<Engine::Material>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getMaterial()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Render>(_name, std::make_shared<Engine::Render>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getShapes()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Transform>(_name, std::make_shared<Engine::Transform>(pointPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Texture>(_name, std::make_shared<Engine::Texture>("Assets/Normal.png"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Shader>(_name, std::make_shared<Engine::Shader>("Assets/Test.vs", "Assets/Test.fs"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::AxisAlignedBoundingBox>(_name, std::make_shared<Engine::AxisAlignedBoundingBox>());
		//Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>(_name, std::make_shared<Engine::PointLight>(glm::vec3(1.0f, 0.95f, 0.95f), 0/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));

	}

	virtual void Cleanup() override {}
	virtual void Update(Engine::DeltaTime deltaTime) override {}
private:
	glm::vec3 pointPos;
};


struct Ground : Engine::Entity
{
public:
	Ground(std::string name, glm::vec3 pos) : Entity(name) {
		position = pos;
	}
	virtual ~Ground() {}
	virtual void Init()override {

		Engine::EntityManager::GetInstance()->AddComponent<Engine::Material>(_name, std::make_shared<Engine::Material>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getMaterial()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Render>(_name, std::make_shared<Engine::Render>(Engine::ResourceManager::GetInstance()->LoadResource("Assets/Box.obj")->getShapes()));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Transform>(_name, std::make_shared<Engine::Transform>(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.1f, 1.0f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Texture>(_name, std::make_shared<Engine::Texture>("Assets/Box.png"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::Shader>(_name, std::make_shared<Engine::Shader>("Assets/Test.vs", "Assets/Test.fs"));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::AxisAlignedBoundingBox>(_name, std::make_shared<Engine::AxisAlignedBoundingBox>());
	}
	virtual void Cleanup() override {}
	virtual void Update(Engine::DeltaTime deltaTime) override {}
private:
	glm::vec3 position;
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
		Engine::EntityManager::GetInstance()->AddEntity<Point>(std::make_shared<Point>("Point", glm::vec3(0.0f, -5.5f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>("Point", std::make_shared<Engine::PointLight>(glm::vec3(1.0f, 0.95f, 0.95f), 0/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));
		Engine::EntityManager::GetInstance()->AddEntity<Point>(std::make_shared<Point>("Point1", glm::vec3(8.0f, -5.5f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>("Point1", std::make_shared<Engine::PointLight>(glm::vec3(1.0f, 0.95f, 0.95f), 1/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));
		Engine::EntityManager::GetInstance()->AddEntity<Point>(std::make_shared<Point>("Point2", glm::vec3(8.0f, -5.5f, 25.0f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>("Point2", std::make_shared<Engine::PointLight>(glm::vec3(1.0f, 0.95f, 0.95f), 2/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));
		Engine::EntityManager::GetInstance()->AddEntity<Point>(std::make_shared<Point>("Point3", glm::vec3(16.0f, -5.5f, 25.0f)));
		Engine::EntityManager::GetInstance()->AddComponent<Engine::PointLight>("Point3", std::make_shared<Engine::PointLight>(glm::vec3(1.0f, 0.95f, 0.95f), 3/*glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f)*/));

		Engine::EntityManager::GetInstance()->AddEntity<Exit>(std::make_shared<Exit>("Exit", glm::vec3(16.0f, -5.8f, 23.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground", glm::vec3(0.0f, -6.0f, 13.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground1", glm::vec3(0.0f, -6.0f, 15.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground2", glm::vec3(0.0f, -6.0f, 17.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground3", glm::vec3(0.0f, -6.0f, 19.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground4", glm::vec3(2.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground5", glm::vec3(4.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground6", glm::vec3(6.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground7", glm::vec3(8.0f, -6.0f, 19.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground8", glm::vec3(8.0f, -6.0f, 17.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground9", glm::vec3(8.0f, -6.0f, 15.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground10", glm::vec3(8.0f, -6.0f, 13.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground11", glm::vec3(6.0f, -6.0f, 13.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground12", glm::vec3(4.0f, -6.0f, 13.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground13", glm::vec3(2.0f, -6.0f, 13.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground14", glm::vec3(10.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground15", glm::vec3(12.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground16", glm::vec3(14.0f, -6.0f, 19.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground17", glm::vec3(16.0f, -6.0f, 19.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground18", glm::vec3(16.0f, -6.0f, 21.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground19", glm::vec3(16.0f, -6.0f, 23.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground20", glm::vec3(16.0f, -6.0f, 25.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground21", glm::vec3(14.0f, -6.0f, 25.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground22", glm::vec3(12.0f, -6.0f, 25.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground23", glm::vec3(10.0f, -6.0f, 25.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground24", glm::vec3(8.0f, -6.0f, 25.0f)));

		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground25", glm::vec3(8.0f, -6.0f, 23.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground26", glm::vec3(8.0f, -6.0f, 21.0f)));
		Engine::EntityManager::GetInstance()->AddEntity<Ground>(std::make_shared<Ground>("Ground27", glm::vec3(8.0f, -6.0f, 19.0f)));
		
		//Engine::EntityManager::GetInstance()->AddEntity<Engine::Camera>(std::make_shared<Engine::Camera>("Camera"));

		//Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Parent" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Parent", std::make_shared<Engine::Transform>( glm::vec3( 0.0f, 0.0f, 5.0f ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Physics>( "Parent", std::make_shared<Engine::Physics>( ) );
		////Engine::EntityManager::GetInstance( )->AddComponent<Engine::DirectionalLight>( "Parent", std::make_shared<Engine::DirectionalLight>( glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), 0.1f, 0.1f ) );
		//
		//Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Child1" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( "Child1", std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getMaterial( ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Child1", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Child1", std::make_shared<Engine::Transform>( glm::vec3( -2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Child1", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Child1", std::make_shared<Engine::Texture>( "Assets/Test.png" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Child1", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::PointLight>( "Child1", std::make_shared<Engine::PointLight>( glm::vec3( 1.0f, 0.25f, 0.125f ), 0, glm::vec3( 0.0f, 1.0f, 0.0f ), 1.0f, 1.0f ) );
		//
		//Engine::EntityManager::GetInstance( )->AddEntity<Player>( std::make_shared<Player>( "Child2" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Material>( "Child2", std::make_shared<Engine::Material>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Box.obj" )->getMaterial( ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Render>( "Child2", std::make_shared<Engine::Render>( Engine::ResourceManager::GetInstance( )->LoadResource( "Assets/Sphere.obj" )->getShapes( ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Transform>( "Child2", std::make_shared<Engine::Transform>( glm::vec3( 2.0f, 0.0f, 5.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Shader>( "Child2", std::make_shared<Engine::Shader>( "Assets/Test.vs", "Assets/Test.fs" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::Texture>( "Child2", std::make_shared<Engine::Texture>( "Assets/Test.png" ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::AxisAlignedBoundingBox>( "Child2", std::make_shared<Engine::AxisAlignedBoundingBox>( ) );
		//Engine::EntityManager::GetInstance( )->AddComponent<Engine::SpotLight>( "Child2", std::make_shared<Engine::SpotLight>( glm::vec3( 0.0f, 0.0f, 1.0f ), 0.9f, 0, glm::vec3( 1.0f, 0.025f, 0.025f ), glm::vec3( 0.0f, 1.0f, 0.0f ), 1.0f, 1.0f, SPOT_LIGHT ) );
		//
		//Engine::EntityManager::GetInstance( )->GetEntity<Player>( "Parent" )->SetChild( "Child1" );
		//Engine::EntityManager::GetInstance( )->GetEntity<Player>( "Parent" )->SetChild( "Child2" );


		while ( window.IsOpen( ) ) {
			deltaTime.Update( );
			//jatka tästä
			if (keyboard.getKey('W'))
			{
				//Engine::EntityManager::GetInstance()->AddComponent<Engine::Transform>("Camera", std::make_shared<Engine::Transform>(glm::vec3(0.0f, 0.0f, 1.0f)));
			}

			//if ( keyboard.getKey( '1' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( '2' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( '3' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			//}
			//if ( keyboard.getKey( '4' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( '5' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( '6' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Parent", PHYS )->AddAngularVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			//}
			//if ( keyboard.getKey( 'W' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 0.0f, 1.0f ) );
			//}
			//if ( keyboard.getKey( 'S' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 0.0f, -1.0f ) );
			//}
			//if ( keyboard.getKey( 'A' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 1.0f, 0.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( 'D' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( -1.0f, 0.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( 'E' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, 1.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( 'Q' ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->AddVelocity( glm::vec3( 0.0f, -1.0f, 0.0f ) );
			//}
			//if ( keyboard.getKey( VK_SPACE ) ) {
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
			//	Engine::EntityManager::GetInstance( )->GetComponent<Engine::Physics>( "Player", PHYS )->SetAngularVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
			//}

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
