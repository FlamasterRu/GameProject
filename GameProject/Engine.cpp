#include "Engine.h"

Engine::Engine()
{
	// Получаем разрешение экрана, создаем окно
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Включаем сглаживание
	m_Setting.antialiasingLevel = 8;



	m_Window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Fullscreen);

	// Включаем вертикальную синхронизацию
	m_Window.setVerticalSyncEnabled(true);

	m_NumberAliveEnemy = numEnemy * lineEnemy;
	m_userMenuInput = 3;
	for (int i = 0; i < lineEnemy * numEnemy; ++i)
	{
		m_Enemy[i] = nullptr;
	}

	m_changeWindow = false;

	keyToFire = Keyboard::Space;
	keyToMoveBot = Keyboard::S;
	keyToMoveLeft = Keyboard::A;
	keyToMoveRight = Keyboard::D;
	keyToMoveTop = Keyboard::W;

}






Engine::~Engine()
{
	for (int i = 0; i < numEnemy * lineEnemy; ++i)
	{
		if (m_Enemy[i] != nullptr)
		{
			delete m_Enemy[i];
		}
	}
}







void Engine::start()
{
	m_changeWindow = false;

	m_NumberAliveEnemy = numEnemy * lineEnemy;

	// Выключаем курсор
	m_Window.setMouseCursorVisible(false);

	m_BackgroundTexture.loadFromFile("Background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	for (int j = 0; j < lineEnemy; ++j)
	{
		for (int i = 0; i < numEnemy; ++i)
		{
			m_Enemy[i + j * numEnemy] = new Enemy();
			m_Enemy[i + j * numEnemy]->setPosition(i * 100 + 450, j * 70 + 100);
			m_Enemy[i + j * numEnemy]->setXRange(i * 100 + 130, i * 100 + 820);
			m_Enemy[i + j * numEnemy]->setYRange(0, 700);
		}
	}

	for (int i = 0; i < numLaser; ++i)
	{
		m_Hero.setLaserNullptr(i);
	}

	// Расчет времени
	Clock clock;

	while (!m_changeWindow)
	{
		// Перезапускаем таймер и записываем отмеренное время в dt
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		try
		{
			input();
			update(dtAsSeconds);
			check();
			draw();
		}
		catch (...)
		{
			m_Window.close();
		}
	}
}











void Engine::check()
{
	////// проверка на вылет лазера и попадание, а также на столкновение героя с мобами
	int i, j;
	Vector2u temp;
	Vector2f botEnemyPosition, botLaserPosition;
	Vector2f topEnemyPosition, topLaserPosition;
	for (i = 0; i < numLaser; ++i)
	{
		if (m_Hero.getLaser(i) != nullptr)
		{
			temp = m_Hero.getLaser(i)->getLaserSprite().getTexture()->getSize();
			topLaserPosition = m_Hero.getLaser(i)->getPosition();
			botLaserPosition.x = float(temp.x);
			botLaserPosition.y = float(temp.y);
			botLaserPosition.x += topLaserPosition.x;
			botLaserPosition.y += topLaserPosition.y;


			//// проверка на вылет из карты
			if (botLaserPosition.y < 0)
			{
				/// вылетел в верх экрана
				delete m_Hero.getLaser(i);
				m_Hero.setLaserNullptr(i);
			}
			if ((botLaserPosition.x < 0) or (topLaserPosition.x > 1920))
			{
				/// вылетел в бок экрана
				delete m_Hero.getLaser(i);
				m_Hero.setLaserNullptr(i);
			}



			///// проверка на попадание по врагу
			for (j = 0; j < numEnemy * lineEnemy; ++j)
			{
				if (m_Enemy[j] != nullptr)
				{

					temp = m_Enemy[j]->getEnemySprite().getTexture()->getSize();
					botEnemyPosition.x = float(temp.x);
					botEnemyPosition.y = float(temp.y);
					topEnemyPosition = m_Enemy[j]->getPosition();
					botEnemyPosition.x += topEnemyPosition.x;
					botEnemyPosition.y += topEnemyPosition.y;


					///// проверяем, залезает ли центр лазера внутрь моба
					botLaserPosition.x = topLaserPosition.x + (botLaserPosition.x - topLaserPosition.x) / 2;
					botLaserPosition.y = topLaserPosition.y + (botLaserPosition.y - topLaserPosition.y) / 2;
					if ((botLaserPosition.x > topEnemyPosition.x) and (botLaserPosition.x < botEnemyPosition.x))
					{
						if ((botLaserPosition.y > topEnemyPosition.y) and (botLaserPosition.y < botEnemyPosition.y))
						{
							//// попал
							if (m_Enemy[j] != nullptr)
							{
								delete m_Enemy[j];
								m_Enemy[j] = nullptr;
								delete m_Hero.getLaser(i);
								m_Hero.setLaserNullptr(i);
								--m_NumberAliveEnemy;
							}
						}
					}
				}
			}
		}
	}   /// Если враги закончились, то очищаем память и надо добавить отображение победы или поражения
	if (m_NumberAliveEnemy == 0)
	{
		m_userMenuInput = ShowMenu;
		m_changeWindow = true;
		//m_Window.close();
	}
}




void Engine::menu()
{
	m_changeWindow = false;

	// Включаем курсор
	m_Window.setMouseCursorVisible(true);

	m_BackgroundTexture.loadFromFile("Menu.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	Cursor cursor;
	cursor.loadFromSystem(Cursor::Arrow);
	m_Window.setMouseCursor(cursor);


	// Расчет времени
	Clock clock;

	while (!m_changeWindow)
	{
		// Перезапускаем таймер и записываем отмеренное время в dt
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		try
		{
			draw();
			input();
		}
		catch (...)
		{
			m_Window.close();
		}
	}

}



void Engine::setting()
{
	m_changeWindow = false;

	m_BackgroundTexture.loadFromFile("Background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	Cursor cursor;
	cursor.loadFromSystem(Cursor::Arrow);
	m_Window.setMouseCursor(cursor);


	for (int i = 0; i < numEnemy * lineEnemy; ++i)
	{
		m_Enemy[i] = nullptr;
	}



	// Расчет времени
	Clock clock;

	while (!m_changeWindow)
	{
		// Перезапускаем таймер и записываем отмеренное время в dt
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		try
		{
			draw();
			input();
		}
		catch (...)
		{
			m_Window.close();
		}
	}


}


int Engine::getUserMenuInput()
{
	return m_userMenuInput;
}



void Engine::drawGame()
{
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
}




void Engine::drawMenu()
{

}



void Engine::drawSetting()
{
	Font font;
	font.loadFromFile("gameFont.ttf");

	Text text1("Setting", font);
	text1.setFillColor(Color::Blue);
	text1.setPosition(930.0, 100.0);





	m_Window.draw(text1);
}



void Engine::updateGameWindow(float dtAsSeconds)
{
	int ifGameOver = 1;
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
	for (int i = 0; i < numLaser; ++i)
	{
		if (m_Hero.getLaser(i) != nullptr)
		{
			m_Hero.getLaser(i)->update(dtAsSeconds);
		}
	}
}



void Engine::updateMenuWindow(float dtAsSeconds)
{

}


void Engine::updateSettingWindow(float dtAsSeconds)
{

}



void Engine::inputInGame()
{
	// Обрабатываем нажатие Escape
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_userMenuInput = ShowMenu;
		m_changeWindow = true;
		//m_Window.close();
		sleep(timeDelayEscape);
	}

	// Обрабатываем нажатие клавиш движения
	if (Keyboard::isKeyPressed(keyToMoveLeft))
	{
		m_Hero.moveLeft();
	}
	else
	{
		m_Hero.stopLeft();
	}

	if (Keyboard::isKeyPressed(keyToMoveRight))
	{
		m_Hero.moveRight();
	}
	else
	{
		m_Hero.stopRight();
	}

	if (Keyboard::isKeyPressed(keyToMoveTop))
	{
		m_Hero.moveTop();
	}
	else
	{
		m_Hero.stopTop();
	}

	if (Keyboard::isKeyPressed(keyToMoveBot))
	{
		m_Hero.moveBot();
	}
	else
	{
		m_Hero.stopBot();
	}


	//// Клавиши стрельбы

	if (Keyboard::isKeyPressed(keyToFire))
	{
		m_Hero.goFire();
	}
	else
	{
		m_Hero.stopFire();
	}
}



void Engine::inputInMenu()
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
		sleep(timeDelayEscape);
	}
}



void Engine::inputInSetting()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_userMenuInput = ShowMenu;
		m_changeWindow = true;
		//m_Window.close();
		sleep(timeDelayEscape);
	}
}


























