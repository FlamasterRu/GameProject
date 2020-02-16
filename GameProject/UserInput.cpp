#include "Engine.h"

void Engine::input()
{
	Time time;
	time = seconds(0.5);
	// обработка клавиш только в игре
	if (m_userMenuInput == StartGame)
	{
		// Обрабатываем нажатие Escape
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_userMenuInput = ShowMenu;
			m_changeWindow = true;
			//m_Window.close();
			sleep(time);
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




	/// обработка курсора мыши только в меню
	if (m_userMenuInput == ShowMenu)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePosition(Mouse::getPosition());
			if ((mousePosition.x > 910) and (mousePosition.x < 1030) and (mousePosition.y > 640) and (mousePosition.y < 700))		// (910, 640)   (1030, 700)
			{
				m_userMenuInput = Exit;
				m_changeWindow = true;
				m_Window.close();
			}
			if ((mousePosition.x > 850) and (mousePosition.x < 1110) and (mousePosition.y > 410) and (mousePosition.y < 480))		// (850, 410) (1110, 480)
			{
				m_userMenuInput = StartGame;
				m_changeWindow = true;
				//m_Window.close();
			}
			if ((mousePosition.x > 890) and (mousePosition.x < 1070) and (mousePosition.y > 540) and (mousePosition.y < 600))		// (890, 540)  (1070, 600)
			{
				m_userMenuInput = OpenSetting;
				m_changeWindow = true;
				//m_Window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_userMenuInput = 0;
			m_changeWindow = true;
			//m_Window.close();
			sleep(time);
		}
	}



	if (m_userMenuInput == OpenSetting)
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_userMenuInput = ShowMenu;
			m_changeWindow = true;
			//m_Window.close();
			sleep(time);
		}
	}

}