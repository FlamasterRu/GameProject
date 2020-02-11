#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	m_Hero.update(dtAsSeconds);

	for (int i = 0; i < numEnemy * lineEnemy; ++i)
	{
		if (m_Enemy[i] != nullptr)
		{
			m_Enemy[i]->update(dtAsSeconds);
		}
	}
	for (int i = 0; i < numLaser; ++i)
	{
		if (m_Hero.getLaser(i) != nullptr)
		{
			m_Hero.getLaser(i)->update(dtAsSeconds);
		}
	}
}













