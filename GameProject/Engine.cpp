#include "Engine.h"

Engine::Engine()
{
	
	// Включаем сглаживание
	m_Setting.antialiasingLevel = 8;

	// Получаем разрешение экрана, создаем окно
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Game",
		Style::Fullscreen);

	// Включаем вертикальную синхронизацию
	m_Window.setVerticalSyncEnabled(true);

	// Выключаем курсор
	m_Window.setMouseCursorVisible(false);

	m_BackgroundTexture.loadFromFile("background.jpg");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	e_Enemy = new Enemy[numEnemy * lineEnemy];
	for (int j = 0; j < lineEnemy; ++j)
	{
		for (int i = 0; i < numEnemy; ++i)
		{
			e_Enemy[i + j * numEnemy].setPositionX(i * 40 + 100);
			e_Enemy[i + j * numEnemy].setPositionY(j * 50 + 20);
			e_Enemy[i + j * numEnemy].setMaxPositionY(360);
			e_Enemy[i + j * numEnemy].setMinPositionY(0);
			e_Enemy[i + j * numEnemy].setMaxPositionX(i * 40 + 100 + 300);
			e_Enemy[i + j * numEnemy].setMinPositionX(i * 40 + 100);
		}
	}

}


Engine::~Engine()
{
	delete[] e_Enemy;
}

void Engine::start()
{
	// Расчет времени
	Clock clock;

	while (m_Window.isOpen())
	{
		// Перезапускаем таймер и записываем отмеренное время в dt
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		try
		{
			input();
			update(dtAsSeconds, clock);
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




}













