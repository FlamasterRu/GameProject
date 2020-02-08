#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	m_Hero.update(dtAsSeconds);

	for (int i = 0; i < numEnemy * lineEnemy; ++i)
	{
		e_Enemy[i].update(dtAsSeconds);
	}
}