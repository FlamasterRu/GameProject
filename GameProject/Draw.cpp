#include "Engine.h"

void Engine::draw()
{
	// ������� ���������� ����
	m_Window.clear(Color::White);


	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(m_Hero.getHeroConvex());  //// ������ ������ �����
	
	for (int i = 0; i < numEnemy * lineEnemy; ++i)   /// ������ ������ 
	{
		m_Window.draw(e_Enemy[i].getEnemyConvex());
	}





	m_Window.display();
}