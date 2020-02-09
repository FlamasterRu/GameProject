#pragma once
#include <SFML/Graphics.hpp>
#include "Laser.h"

const float heroScale = 10.0;
const int heroSpeed = 300;
const int numLaser = 1000;    /// максимальное количество лазеров на экране


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// Координаты левого верхнего угла примоугольника, который описывает фигурку героя

	ConvexShape m_convex;

	Texture m_Texture;
	const Texture* m_ptrTexture;

	Laser* m_laser[numLaser];

	int m_health;

	// Логические переменные для отслеживания направления движения
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;
	bool m_GoFire;

	// Скорость в пикселях в секунду
	float m_Speed;

	float m_lastFire;


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
	void update(float elapsedTime, Clock clock);

	/// Перемещаем фигуру героя
	void changePosition();

	ConvexShape getHeroConvex();

	void fire();

	Laser* getLaser(int num);

	void goFire();
	
	void stopFire();

};