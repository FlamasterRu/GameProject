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

	Laser* m_laser[numLaser];		// Лазеры, выпущенные героем


	// Логические переменные для отслеживания направления движения
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;
	bool m_GoFire;

	// Скорость в пикселях в секунду
	float m_Speed;

	float m_LastFire;		//Сколько секунд назад был последний выстрел (чтобы не стрелять как пулемёт)


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
	void setPosition(Vector2f position);
	void setPosition(float positionX, float positionY);


	Sprite getHeroSprite();
	Laser* getLaser(int num);
	Vector2f getPosition();


	// Эта функция будет вызываться на каждый кадр
	void update(float elapsedTime);

	void fire();

};