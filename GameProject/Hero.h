#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hero
{

private:

	Vector2f m_Position;

	Sprite m_Sprite;

	Texture m_Texture;

	// Логические переменные для отслеживания направления движения
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;

	// Скорость в пикселях в секунду
	float m_Speed;


public:

	Hero();

	// Для отправки спрайта в главную функцию
	Sprite getSprite();

	// Для движения
	void moveLeft();

	void moveRight();

	void moveTop();

	void moveBot();

	// Прекращение движения
	void stopLeft();

	void stopRight();

	void stopTop();

	void stopBot();

	// Эта функция будет вызываться на каждый кадр
	void update(float elapsedTime);

};