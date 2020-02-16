#include "Engine.h"
#include <Windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	Engine engine;

	while (engine.getUserMenuInput())
	{
		switch (engine.getUserMenuInput())
		{
		case Exit:
			break;
		case StartGame:
			engine.start();
			break;
		case OpenSetting:
			engine.setting();
			break;
		case ShowMenu:
			engine.menu();
			break;
		default:
			break;
		}
	}



	// Останавливаем программу программу, когда движок остановлен
	return 0;
}



