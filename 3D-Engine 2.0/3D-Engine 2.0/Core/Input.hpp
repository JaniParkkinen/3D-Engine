#ifndef Engine_Input_hpp
#define Engine_Input_hpp
#include <vector>



namespace Engine {

	//Keyboard input class
	class Keyboard {
	public:
		int numKeycodes = 256;
		unsigned int keyCode = 0;
		
		void update();

		bool getKey(int keycode);
		void getKeyDown(int keycode);
		void getKeyUp(int keycode);

	private:
		std::vector<int> currentKeys = std::vector<int>();
		std::vector<int> downKeys = std::vector<int>();
		std::vector<int> upKeys = std::vector<int>();
		std::vector<bool> boolVec = std::vector<bool>(256, false);


	};

	//Mouse input class
	class Mouse {
	public:
		int numMouseButtons = 5;
		unsigned int mouseButton = 0;

		void update();

	private:
		std::vector<int> currentMouse = std::vector<int>();
		std::vector<int> downMouse = std::vector<int>();
		std::vector<int> upMouse = std::vector<int>();



	};

}





#endif