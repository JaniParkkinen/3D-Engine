#include <Core/Input.hpp>
#include <iostream>
#include <Windows.h>
namespace Engine {
	//Keyboard
	void Keyboard::update()
	{
		upKeys.clear();
		for (int i = 0; i < numKeycodes; i++)
		{
			if (!getKey(i) && currentKeys[i])
			{
				upKeys[i];
			}
		}
		downKeys.clear();
		for (int i = 0; i < numKeycodes; i++)
		{
			if (getKey(i) && !currentKeys[i])
			{
				downKeys[i];
			}
		}
		currentKeys.clear();
		for (int i = 0; i < numKeycodes; i++)
		{
			if (getKey(i))
			{
				currentKeys[i];
			}
		}
	}

	bool Keyboard::getKey(int keycode)
	{
		return boolVec[keycode];
		//return(GetAsyncKeyState(keycode) & 0x8000) != 0;
	}
	void Keyboard::getKeyDown(int keycode)
	{
		boolVec[keycode] = true;
		/*return(GetAsyncKeyState(keycode) & 0x8000) != 0;*/
	}
	void Keyboard::getKeyUp(int keycode)
	{
		boolVec[keycode] = false;
		//if (upKeys[keycode])
		//{
		//	return true;
		//}
		//else
		//	return false;
		//return(GetAsyncKeyState(keycode) & 0x8000) != 0;
	}


}