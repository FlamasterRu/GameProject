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

	stringKeyToMoveRight = "D";
	stringKeyToMoveLeft = "A";
	stringKeyToMoveTop = "W";
	stringKeyToMoveBot = "S";
	stringKeyToFire = "Space";

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
	Rect<float> temp;
	float PositionX, PositionY = VideoMode::getDesktopMode().height, resolution = VideoMode::getDesktopMode().width;
	Color SpaseBlue(63, 72, 204);
	Font font;
	font.loadFromFile("gameFont.ttf");


	Text text1("Setting", font);
	text1.setFillColor(SpaseBlue);
	temp = text1.getGlobalBounds();
	PositionX = (resolution - temp.width) / 2.0;
	text1.setPosition(PositionX, PositionY / 10.0);
	text1.setStyle(Text::Bold);
	text1.setCharacterSize(38);

	Text text2("Moving", font);
	text2.setFillColor(SpaseBlue);
	PositionX = resolution / 4.0;
	PositionY /= 5.0;
	text2.setPosition(PositionX, PositionY);
	PositionY += text2.getCharacterSize() * 3.0;
	text2.setStyle(Text::Bold);
	text2.setCharacterSize(34);

	Text text3("Up: " + stringKeyToMoveTop, font);
	text3.setFillColor(SpaseBlue);
	text3.setPosition(PositionX, PositionY);
	PositionY += text3.getCharacterSize() * 1.5;

	Text text4("Down: " + stringKeyToMoveBot, font);
	text4.setFillColor(SpaseBlue);
	text4.setPosition(PositionX, PositionY);
	PositionY += text4.getCharacterSize() * 1.5;

	Text text5("Left: " + stringKeyToMoveLeft, font);
	text5.setFillColor(SpaseBlue);
	text5.setPosition(PositionX, PositionY);
	PositionY += text5.getCharacterSize() * 1.5;

	Text text6("Right: " + stringKeyToMoveRight, font);
	text6.setFillColor(SpaseBlue);
	text6.setPosition(PositionX, PositionY);
	PositionY += text6.getCharacterSize() * 5.0;

	Text text7("Fire", font);
	text7.setFillColor(SpaseBlue);
	text7.setPosition(PositionX, PositionY);
	PositionY += text7.getCharacterSize() * 3.0;
	text7.setStyle(Text::Bold);
	text7.setCharacterSize(34);

	Text text8("Laser fire: " + stringKeyToFire, font);
	text8.setFillColor(SpaseBlue);
	text8.setPosition(PositionX, PositionY);
	PositionY += text8.getCharacterSize() * 1.5;



	m_Window.draw(text1);
	m_Window.draw(text2);
	m_Window.draw(text3);
	m_Window.draw(text4);
	m_Window.draw(text5);
	m_Window.draw(text6);
	m_Window.draw(text7);
	m_Window.draw(text8);
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
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i resolution;
		bool flag = 1;
		resolution.x = VideoMode::getDesktopMode().width;
		resolution.y = VideoMode::getDesktopMode().height / 5;
		Vector2i mousePosition(Mouse::getPosition());

		if ((mousePosition.x > resolution.x / 4) and (mousePosition.x < resolution.x / 4 + 150))
		{
			if ((mousePosition.y > resolution.y + 90) and (mousePosition.y < resolution.y + 120))
			{
				// up
				keyToMoveTop = returnPressedKey();
				stringKeyToMoveTop = pressedButtomAsString(keyToMoveTop);
			}
			if ((mousePosition.y > resolution.y + 135) and (mousePosition.y < resolution.y + 165))
			{
				// down
				keyToMoveBot = returnPressedKey();
				stringKeyToMoveBot = pressedButtomAsString(keyToMoveBot);
			}
			if ((mousePosition.y > resolution.y + 180) and (mousePosition.y < resolution.y + 210))
			{
				// left
				keyToMoveLeft = returnPressedKey();
				stringKeyToMoveLeft = pressedButtomAsString(keyToMoveLeft);
			}
			if ((mousePosition.y > resolution.y + 225) and (mousePosition.y < resolution.y + 255))
			{
				// right
				keyToMoveRight = returnPressedKey();
				stringKeyToMoveRight = pressedButtomAsString(keyToMoveRight);
			}
			if ((mousePosition.y > resolution.y + 465) and (mousePosition.y < resolution.y + 495))
			{
				// fire
				keyToFire = returnPressedKey();
				stringKeyToFire = pressedButtomAsString(keyToFire);
			}
		}






	}


	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_userMenuInput = ShowMenu;
		m_changeWindow = true;
		//m_Window.close();
		sleep(timeDelayEscape);
	}
}



std::string Engine::keyToString(Keyboard::Key key)
{

	return "5";
}




Keyboard::Key Engine::pressedButtom()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Q))
	{
		return Keyboard::Key::Q;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		return Keyboard::Key::W;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::E))
	{
		return Keyboard::Key::E;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::R))
	{
		return Keyboard::Key::R;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::T))
	{
		return Keyboard::Key::T;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Y))
	{
		return Keyboard::Key::Y;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::U))
	{
		return Keyboard::Key::U;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::I))
	{
		return Keyboard::Key::I;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::O))
	{
		return Keyboard::Key::O;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::P))
	{
		return Keyboard::Key::P;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		return Keyboard::Key::A;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		return Keyboard::Key::S;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		return Keyboard::Key::D;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::F))
	{
		return Keyboard::Key::F;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::G))
	{
		return Keyboard::Key::G;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::H))
	{
		return Keyboard::Key::H;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::J))
	{
		return Keyboard::Key::J;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::K))
	{
		return Keyboard::Key::K;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::L))
	{
		return Keyboard::Key::L;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Z))
	{
		return Keyboard::Key::Z;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::X))
	{
		return Keyboard::Key::X;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::C))
	{
		return Keyboard::Key::C;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::V))
	{
		return Keyboard::Key::V;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::B))
	{
		return Keyboard::Key::B;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::N))
	{
		return Keyboard::Key::N;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::M))
	{
		return Keyboard::Key::M;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		return Keyboard::Key::Num1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		return Keyboard::Key::Num2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		return Keyboard::Key::Num3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		return Keyboard::Key::Num4;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		return Keyboard::Key::Num5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		return Keyboard::Key::Num6;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		return Keyboard::Key::Num7;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		return Keyboard::Key::Num8;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num9))
	{
		return Keyboard::Key::Num9;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num0))
	{
		return Keyboard::Key::Num0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad1))
	{
		return Keyboard::Key::Numpad1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad2))
	{
		return Keyboard::Key::Numpad2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad3))
	{
		return Keyboard::Key::Numpad3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad4))
	{
		return Keyboard::Key::Numpad4;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad5))
	{
		return Keyboard::Key::Numpad5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad6))
	{
		return Keyboard::Key::Numpad6;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad7))
	{
		return Keyboard::Key::Numpad7;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad8))
	{
		return Keyboard::Key::Numpad8;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad9))
	{
		return Keyboard::Key::Numpad9;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Numpad0))
	{
		return Keyboard::Key::Numpad0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		return Keyboard::Key::Down;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		return Keyboard::Key::Left;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		return Keyboard::Key::Right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		return Keyboard::Key::Up;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Tab))
	{
		return Keyboard::Key::Tab;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::LShift))
	{
		return Keyboard::Key::LShift;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::RShift))
	{
		return Keyboard::Key::RShift;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::LControl))
	{
		return Keyboard::Key::LControl;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::RControl))
	{
		return Keyboard::Key::RControl;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::LAlt))
	{
		return Keyboard::Key::LAlt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::RAlt))
	{
		return Keyboard::Key::RAlt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		return Keyboard::Key::Space;
	}
	else
	{
		return Keyboard::Key::Unknown;
	}
}






Keyboard::Key Engine::returnPressedKey()
{
	Keyboard::Key temp = Keyboard::Key::Unknown;
	Color SpaseBlue(63, 72, 204);
	Font font;
	font.loadFromFile("gameFont.ttf");
	Text text("Press Key", font);
	text.setFillColor(SpaseBlue);
	text.setPosition(VideoMode::getDesktopMode().width / 4, VideoMode::getDesktopMode().height * 0.9);

	m_Window.clear(Color::White);
	m_Window.draw(m_BackgroundSprite);
	m_Window.draw(text);
	drawSetting();
	m_Window.display();
	while (temp == Keyboard::Key::Unknown)
	{
		temp = pressedButtom();
	}
	return temp;

}



std::string Engine::pressedButtomAsString(Keyboard::Key key)
{
	if (key == (Keyboard::Key::Q))
	{
		return "Q";
	}
	else if (key == (Keyboard::Key::W))
	{
		return "W";
	}
	else if (key == (Keyboard::Key::E))
	{
		return "E";
	}
	else if (key == (Keyboard::Key::R))
	{
		return "R";
	}
	else if (key == (Keyboard::Key::T))
	{
		return "T";
	}
	else if (key == (Keyboard::Key::Y))
	{
		return "Y";
	}
	else if (key == (Keyboard::Key::U))
	{
		return "U";
	}
	else if (key == (Keyboard::Key::I))
	{
		return "I";
	}
	else if (key == (Keyboard::Key::O))
	{
		return "O";
	}
	else if (key == (Keyboard::Key::P))
	{
		return "P";
	}
	else if (key == (Keyboard::Key::A))
	{
		return "A";
	}
	else if (key == (Keyboard::Key::S))
	{
		return "S";
	}
	else if (key == (Keyboard::Key::D))
	{
		return "D";
	}
	else if (key == (Keyboard::Key::F))
	{
		return "F";
	}
	else if (key == (Keyboard::Key::G))
	{
		return "G";
	}
	else if (key == (Keyboard::Key::H))
	{
		return "H";
	}
	else if (key == (Keyboard::Key::J))
	{
		return "J";
	}
	else if (key == (Keyboard::Key::K))
	{
		return "K";
	}
	else if (key == (Keyboard::Key::L))
	{
		return "L";
	}
	else if (key == (Keyboard::Key::Z))
	{
		return "Z";
	}
	else if (key == (Keyboard::Key::X))
	{
		return "X";
	}
	else if (key == (Keyboard::Key::C))
	{
		return "C";
	}
	else if (key == (Keyboard::Key::V))
	{
		return "V";
	}
	else if (key == (Keyboard::Key::B))
	{
		return "B";
	}
	else if (key == (Keyboard::Key::N))
	{
		return "N";
	}
	else if (key == (Keyboard::Key::M))
	{
		return "M";
	}
	else if (key == (Keyboard::Key::Num1))
	{
		return "Num1";
	}
	else if (key == (Keyboard::Key::Num2))
	{
		return "Num2";
	}
	else if (key == (Keyboard::Key::Num3))
	{
		return "Num3";
	}
	else if (key == (Keyboard::Key::Num4))
	{
		return "Num4";
	}
	else if (key == (Keyboard::Key::Num5))
	{
		return "Num5";
	}
	else if (key == (Keyboard::Key::Num6))
	{
		return "Num6";
	}
	else if (key == (Keyboard::Key::Num7))
	{
		return "Num7";
	}
	else if (key == (Keyboard::Key::Num8))
	{
		return "Num8";
	}
	else if (key == (Keyboard::Key::Num9))
	{
		return "Num9";
	}
	else if (key == (Keyboard::Key::Num0))
	{
		return "Num0";
	}
	else if (key == (Keyboard::Key::Numpad1))
	{
		return "Numpad1";
	}
	else if (key == (Keyboard::Key::Numpad2))
	{
		return "Numpad2";
	}
	else if (key == (Keyboard::Key::Numpad3))
	{
		return "Numpad3";
	}
	else if (key == (Keyboard::Key::Numpad4))
	{
		return "Numpad4";
	}
	else if (key == (Keyboard::Key::Numpad5))
	{
		return "Numpad5";
	}
	else if (key == (Keyboard::Key::Numpad6))
	{
		return "Numpad6";
	}
	else if (key == (Keyboard::Key::Numpad7))
	{
		return "Numpad7";
	}
	else if (key == (Keyboard::Key::Numpad8))
	{
		return "Numpad8";
	}
	else if (key == (Keyboard::Key::Numpad9))
	{
		return "Numpad9";
	}
	else if (key == (Keyboard::Key::Numpad0))
	{
		return "Numpad0";
	}
	else if (key == (Keyboard::Key::Down))
	{
		return "Down";
	}
	else if (key == (Keyboard::Key::Left))
	{
		return "Left";
	}
	else if (key == (Keyboard::Key::Right))
	{
		return "Right";
	}
	else if (key == (Keyboard::Key::Up))
	{
		return "Up";
	}
	else if (key == (Keyboard::Key::Tab))
	{
		return "Tab";
	}
	else if (key == (Keyboard::Key::LShift))
	{
		return "LShift";
	}
	else if (key == (Keyboard::Key::RShift))
	{
		return "RShift";
	}
	else if (key == (Keyboard::Key::LControl))
	{
		return "LControl";
	}
	else if (key == (Keyboard::Key::RControl))
	{
		return "RControl";
	}
	else if (key == (Keyboard::Key::LAlt))
	{
		return "LAlt";
	}
	else if (key == (Keyboard::Key::RAlt))
	{
		return "RAlt";
	}
	else if (key == (Keyboard::Key::Space))
	{
		return "Space";
	}
	else
	{
		return "Unknown";
	}
}




















