#pragma once
#include <SFML/Graphics.hpp>
#include "Laser.h"

const int heroSpeed = 400;
const int numLaser = 50;    /// максимальное количество лазеров на экране


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// Координаты левого верхнего угла примоугольника, который описывает фигурку героя

	Sprite m_Sprite;

	Texture m_Texture;

	Laser* m_laser[numLaser];

	int m_Health;

	// Логические переменные для отслеживания направления движения
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;
	bool m_GoFire;

	// Скорость в пикселях в секунду
	float m_Speed;

	float m_LastFire;


public:

	Hero();
	~Hero();


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

	// Для стрельбы
	void goFire();
	void stopFire();


	void setLaserNullptr(int num);


	Sprite getHeroSprite();
	Laser* getLaser(int num);


	// Эта функция будет вызываться на каждый кадр
	void update(float elapsedTime);

	void fire();

};