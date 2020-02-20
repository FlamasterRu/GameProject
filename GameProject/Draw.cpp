#include "Engine.h"

void Engine::draw()
{
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);

	m_Window.draw(m_BackgroundSprite);

	if (m_userMenuInput == StartGame)
	{
		drawGame();
	}
	if (m_userMenuInput == ShowMenu)
	{
		drawMenu();
	}
	if (m_userMenuInput == OpenSetting)
	{
		drawSetting();
	}


	m_Window.display();
}













