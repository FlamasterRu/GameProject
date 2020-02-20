#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{

	if (m_userMenuInput == StartGame)
	{
		updateGameWindow(dtAsSeconds);
	}
	if (m_userMenuInput == OpenSetting)
	{
		updateSettingWindow(dtAsSeconds);
	}
	if (m_userMenuInput == ShowMenu)
	{
		updateMenuWindow(dtAsSeconds);
	}

}













