#include "Engine.h"

Engine::Engine()
{
	
	// �������� �����������
	m_Setting.antialiasingLevel = 8;

	// �������� ���������� ������, ������� ����
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Game",
		Style::Fullscreen);

	// �������� ������������ �������������
	m_Window.setVerticalSyncEnabled(true);

	// ��������� ������
	m_Window.setMouseCursorVisible(false);

	m_BackgroundTexture.loadFromFile("background.jpg");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

}

void Engine::start()
{
	// ������ �������
	Clock clock;

	while (m_Window.isOpen())
	{
		// ������������� ������ � ���������� ���������� ����� � dt
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}