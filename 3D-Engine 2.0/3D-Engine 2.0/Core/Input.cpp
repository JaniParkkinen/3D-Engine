#include <Core/Input.hpp>
#include <iostream>
#include <Windows.h>
namespace Engine {
	//Keyboard
	void Keyboard::update()
	{
		lastKeys = currentKeys;
	}

	bool Keyboard::getKey(int keycode)
	{
		return currentKeys[keycode];
	}
	bool Keyboard::getKeyDown(int keycode)
	{
		if (lastKeys[keycode] != currentKeys[keycode] && currentKeys[keycode])
		{
			return true;
		}
		return false;
	}
	bool Keyboard::getKeyUp(int keycode)
	{
		if (lastKeys[keycode] != currentKeys[keycode] && lastKeys[keycode])
		{
			return true;
		}
		return false;
	}

	void Keyboard::keyDown(int keycode)
	{
		currentKeys[keycode] = true;
	}
	void Keyboard::keyUp(int keycode)
	{
		currentKeys[keycode] = false;
	}

	//Mouse
	void Mouse::update()
	{
		mouseWheel = 0;
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
		lastMouse = currentMouse;
	}

	bool Mouse::getMouse(int mouseButton)
	{
		return currentMouse[mouseButton];
	}
	bool Mouse::getMouseDown(int mouseButton)
	{
		if (lastMouse[mouseButton] != currentMouse[mouseButton] && currentMouse[mouseButton])
		{
			return true;
		}
		return false;
	}
	bool Mouse::getMouseUp(int mouseButton)
	{
		if (lastMouse[mouseButton] != currentMouse[mouseButton] && lastMouse[mouseButton])
		{
			return true;
		}
		return false;
	}
	bool Mouse::mouseWheelUp()
	{
		return mouseWheel > 0;
	}
	bool Mouse::mouseWheelDown()
	{
		return mouseWheel < 0;
	}

	void Mouse::mouseWheelIn(int wheel)
	{
		mouseWheel = wheel;
	}
	void Mouse::mouseEvent(int keycode, glm::vec2 mousePos)
	{
		this->mousePos = mousePos;
		if (keycode & MK_LBUTTON) {
			currentMouse[MK_LBUTTON] = true;
		} else {
			currentMouse[MK_LBUTTON] = false;
		}
		if (keycode & MK_RBUTTON) {
			currentMouse[MK_RBUTTON] = true;
		}
		else {
			currentMouse[MK_RBUTTON] = false;
		}
		if (keycode & MK_MBUTTON) {
			currentMouse[MK_MBUTTON] = true;
		}
		else {
			currentMouse[MK_MBUTTON] = false;
		}
		if (keycode & MK_XBUTTON1) {
			currentMouse[MK_XBUTTON1] = true;
		}
		else {
			currentMouse[MK_XBUTTON1] = false;
		}
		if (keycode & MK_XBUTTON2) {
			currentMouse[MK_XBUTTON2] = true;
		}
		else {
			currentMouse[MK_XBUTTON2] = false;
		}
	}
	//void Mouse::mouseDown(int mouseButton, glm::vec2 mousePos)
	//{
	//	currentMouse[mouseButton] = true;
	//	this->mousePos = mousePos;
	//}
	//void Mouse::mouseUp(int mouseButton, glm::vec2 mousePos)
	//{
	//	currentMouse[mouseButton] = false;
	//	this->mousePos = mousePos;
	//}

}