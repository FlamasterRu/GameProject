#pragma once
#include <SFML/Graphics.hpp>

const float heroScale = 10.0;
const int speedHero = 300;


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// Координаты левого верхнего угла примоугольника, который описывает фигурку героя

	ConvexShape m_convex;

	Texture m_Texture;
	const Texture* m_ptrTexture;

	// Логические переменные для отслеживания направления движения
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;

	// Скорость в пикселях в секунду
	float m_Speed;


public:

	Hero();


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

	/// Перемещаем фигуру героя
	void changePosition();

	ConvexShape getHeroConvex();

};