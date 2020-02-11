#include "Engine.h"

void Engine::draw()
{
	// Стираем предыдущий кадр
	m_Window.clear(Color::White);


	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(m_Hero.getHeroSprite());  //// рисуем фигуру героя
	
	for (int i = 0; i < numEnemy * lineEnemy; ++i)   /// рисует врагов 
	{
		if (m_Enemy[i] != nullptr)
		{
			m_Window.draw(m_Enemy[i]->getEnemySprite());
		}
	}

	for (int i = 0; i < numLaser; ++i)
	{
		if (m_Hero.getLaser(i) != nullptr)
		{
			m_Window.draw(m_Hero.getLaser(i)->getLaserSprite());
		}
	}

	

	m_Window.display();
}













