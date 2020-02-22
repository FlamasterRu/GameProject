#include "Enemy.h"


Enemy::Enemy()
{

	e_Speed.x = enemySpeedX;
	e_Speed.y = enemySpeedY;


	e_Position.x = 0;
	e_Position.y = 0;

	e_XRange.x = 0;
	e_XRange.y = 0;

	e_YRange.x = 0;
	e_YRange.y = 0;


	// Загрузка текстуры из папки, в которой исполняемый файл
	e_Texture.loadFromFile("Enemy.png");    //// 70*70  размер в пикселях

	e_Sprite.setTexture(e_Texture);

}





void Enemy::setPosition(Vector2f position)
{
	e_Position = position;
}


void Enemy::setPosition(float x, float y)
{
	e_Position.x = x;
	e_Position.y = y;
}



void Enemy::setXRange(Vector2f xRange)
{
	e_XRange = xRange;
}


void Enemy::setXRange(float xLeft, float xRight)
{
	e_XRange.x = xLeft;
	e_XRange.y = xRight;
}


void Enemy::setYRange(Vector2f yRange)
{
	e_YRange = yRange;
}


void Enemy::setYRange(float yLeft, float yRight)
{
	e_YRange.x = yLeft;
	e_YRange.y = yRight;
}




Vector2f Enemy::getPosition()
{
	return e_Position;
}


Sprite Enemy::getEnemySprite()
{
	return e_Sprite;
}



// Вызывается на каждый кадр и перемещает моба в зависимости от текущей позиции, скорости и прошедшего времени
void Enemy::update(float elapsedTime)
{
	/// Проверка на вылет за пределы экрана лежит на функции check, класса Engine!!!!
	e_Position.x += e_Speed.x * elapsedTime;
	e_Position.y += e_Speed.y * elapsedTime;

	if (e_Position.x < e_XRange.x)
	{
		e_Speed.x *= -1;    /// Если дошёл правого до края - разворачиваем моба
	}

	if (e_Position.x > e_XRange.y)
	{
		e_Speed.x *= -1;    /// Если дошёл левого до края - разворачиваем моба
	}

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	if ((e_Position.x > resolution.x) or (e_Position.x < -70))
	{
		// Вышел за пределы экрана
	}
	if ((e_Position.y > resolution.y) or (e_Position.y < -70))
	{
		// Вышел за пределы экрана
	}


	e_Sprite.setPosition(e_Position);
}
























