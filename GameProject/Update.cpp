#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	int ifGameOver = 1;



	if (m_userMenuInput == StartGame)
	{
		m_Hero.update(dtAsSeconds);


		for (int i = 0; i < numEnemy * lineEnemy; ++i)
		{
			if (m_Enemy[i] != nullptr)
			{
				ifGameOver = m_Enemy[i]->update(dtAsSeconds);
				if (ifGameOver == ShowMenu)
				{
					/// если кто-то перечек черту, то поражение, очищаем память и надо добавить окно поражения
					m_userMenuInput = ShowMenu;
					for (int i = 0; i < numEnemy * lineEnemy; ++i)
					{
						if (m_Enemy[i] != nullptr)
						{
							delete m_Enemy[i];
						}
						m_Enemy[i] = nullptr;
					}
					m_changeWindow = true;
					//m_Window.close();
					break;
				}
			}
		}
	}

	if (m_userMenuInput == StartGame)
	{
		for (int i = 0; i < numLaser; ++i)
		{
			if (m_Hero.getLaser(i) != nullptr)
			{
				m_Hero.getLaser(i)->update(dtAsSeconds);
			}
		}
	}


}













