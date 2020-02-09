#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds, Clock clock)
{
	m_Hero.update(dtAsSeconds, clock);

	for (int i = 0; i < numEnemy * lineEnemy; ++i)
	{
		e_Enemy[i].update(dtAsSeconds);
	}
	for (int i = 0; i < numLaser; ++i)
	{
		if (m_Hero.getLaser(i) != nullptr)
		{
			m_Hero.getLaser(i)->update(dtAsSeconds);
		}
	}
}













