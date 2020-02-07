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

		input();
		update(dtAsSeconds);
		draw();
	}
}