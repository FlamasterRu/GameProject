#include "Engine.h"

void Engine::draw()
{
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);


	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(m_Hero.getSprite());


	m_Window.display();
}