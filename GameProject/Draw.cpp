#include "Engine.h"

void Engine::draw()
{
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);


	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(m_Hero.getHeroConvex());  //// рисуем фигуру героя
	
	for (int i = 0; i < numEnemy * lineEnemy; ++i)   /// рисует врагов 
	{
		m_Window.draw(e_Enemy[i].getEnemyConvex());
	}





	m_Window.display();
}