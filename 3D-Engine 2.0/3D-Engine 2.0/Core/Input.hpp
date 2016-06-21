#ifndef Engine_Input_hpp
#define Engine_Input_hpp
#include <vector>
#include <GLM/glm.hpp>



namespace Engine {

	//Keyboard input class
	class Keyboard {
	public:
		void update( );

		bool getKey( int keycode );
		bool getKeyDown( int keycode );
		bool getKeyUp( int keycode );

		void keyDown( int keycode );
		void keyUp( int keycode );

	private:
		std::vector<bool> currentKeys = std::vector<bool>( 256, false );
		std::vector<bool> lastKeys = std::vector<bool>( 256, false );


	};

	//Mouse input class
	class Mouse {
	public:
		void update( );

		bool getMouse( int mousebutton );
		bool getMouseDown( int mousebutton );
		bool getMouseUp( int mousebutton );
		bool mouseWheelUp( );
		bool mouseWheelDown( );

		glm::vec2 getPosition( );
		void mouseWheelIn( int wheel );
		void mouseEvent( int keycode, glm::vec2 mousePos );
		//void mouseDown(int keycode, glm::vec2 mousePos);
		//void mouseUp(int keycode, glm::vec2 mousePos);

	private:
		std::vector<bool> currentMouse = std::vector<bool>( 256, false );
		std::vector<bool> lastMouse = std::vector<bool>( 256, false );
		int mouseWheel = 0;
		glm::vec2 mousePos;

	};

}





#endif