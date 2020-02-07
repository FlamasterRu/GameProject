#include "Engine.h"

void Engine::draw()
{
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);


	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(m_Hero.getHeroConvex());  //// рисуем фигуру героя

	//// Добавить сюда отображение врагов




	m_Window.display();
}