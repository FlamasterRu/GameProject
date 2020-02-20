#include "Engine.h"

void Engine::input()
{

	if (m_userMenuInput == StartGame)
	{
		inputInGame();
	}
	if (m_userMenuInput == ShowMenu)
	{
		inputInMenu();
	}
	if (m_userMenuInput == OpenSetting)
	{
		inputInSetting();
	}

}