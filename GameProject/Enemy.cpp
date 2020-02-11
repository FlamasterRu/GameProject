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

	e_Health = 1;
	e_Damage = 1;


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


void Enemy::setDamage(int damage)
{
	e_Damage = damage;
}


void Enemy::setHealth(int health)
{
	e_Health = health;
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




void Enemy::update(float elapsedTime)
{
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

	if (e_Position.y > e_YRange.y)
	{
		///// Поражение.  
		//throw("lose");
	}

	e_Sprite.setPosition(e_Position);
}
























