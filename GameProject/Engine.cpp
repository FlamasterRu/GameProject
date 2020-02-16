#include "Engine.h"

Engine::Engine()
{
	// �������� ���������� ������, ������� ����
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// �������� �����������
	m_Setting.antialiasingLevel = 8;



	m_Window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Fullscreen);

	// �������� ������������ �������������
	m_Window.setVerticalSyncEnabled(true);

	m_NumberAliveEnemy = numEnemy * lineEnemy;
	m_userMenuInput = 3;
	for (int i = 0; i < lineEnemy * numEnemy; ++i)
	{
			m_Enemy[i] = nullptr;
	}

	m_changeWindow = false;

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

	// ��������� ������
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

	// ������ �������
	Clock clock;

	while (!m_changeWindow)
	{
		// ������������� ������ � ���������� ���������� ����� � dt
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
	////// �������� �� ����� ������ � ���������, � ����� �� ������������ ����� � ������
	int i , j;
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


			//// �������� �� ����� �� �����
			if (botLaserPosition.y < 0)
			{
				/// ������� � ���� ������
				delete m_Hero.getLaser(i);
				m_Hero.setLaserNullptr(i);
			}
			if ((botLaserPosition.x < 0) or (topLaserPosition.x > 1920))
			{
				/// ������� � ��� ������
				delete m_Hero.getLaser(i);
				m_Hero.setLaserNullptr(i);
			}



			///// �������� �� ��������� �� �����
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


					///// ���������, �������� �� ����� ������ ������ ����
					botLaserPosition.x = topLaserPosition.x + (botLaserPosition.x - topLaserPosition.x) / 2;
					botLaserPosition.y = topLaserPosition.y + (botLaserPosition.y - topLaserPosition.y) / 2;
					if ((botLaserPosition.x > topEnemyPosition.x) and (botLaserPosition.x < botEnemyPosition.x))
					{
						if ((botLaserPosition.y > topEnemyPosition.y) and (botLaserPosition.y < botEnemyPosition.y))
						{
							//// �����
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
	}   /// ���� ����� �����������, �� ������� ������ � ���� �������� ����������� ������ ��� ���������
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

	// �������� ������
	m_Window.setMouseCursorVisible(true);

	m_BackgroundTexture.loadFromFile("Menu.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	Cursor cursor;
	cursor.loadFromSystem(Cursor::Arrow);
	m_Window.setMouseCursor(cursor);


	// ������ �������
	Clock clock;

	while (!m_changeWindow)
	{
		// ������������� ������ � ���������� ���������� ����� � dt
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


	// ������ �������
	Clock clock;

	while (!m_changeWindow)
	{
		// ������������� ������ � ���������� ���������� ����� � dt
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




























