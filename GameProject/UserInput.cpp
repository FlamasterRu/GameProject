#include "Engine.h"

void Engine::input()
{
	// Обрабатываем нажатие Escape
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	// Обрабатываем нажатие клавиш движения
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_Hero.moveLeft();
	}
	else
	{
		m_Hero.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_Hero.moveRight();
	}
	else
	{
		m_Hero.stopRight();
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_Hero.moveTop();
	}
	else
	{
		m_Hero.stopTop();
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_Hero.moveBot();
	}
	else
	{
		m_Hero.stopBot();
	}     


	//// Клавиши стрельбы

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		m_Hero.goFire();
	}
	else
	{
		m_Hero.stopFire();
	}


}