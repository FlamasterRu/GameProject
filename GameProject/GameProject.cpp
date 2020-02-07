#include "Engine.h"
#include <Windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	Engine engine;

	engine.start();

	// Останавливаем программу программу, когда движок остановлен
	return 0;
}