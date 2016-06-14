#include <iostream>

#include <Core/3DEngine.hpp>

Engine::Window window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_SIZE:
		window.Resize();
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int main() {
	window.createWindow("3D-Engine", glm::vec2(800.0f, 600.0f), glm::vec2(0.0f, 0.0f), "", "", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::Time deltaTime;

	while (window.IsOpen()) {
		deltaTime.Update();

		window.getMessage();
	};

	exit(0);
};