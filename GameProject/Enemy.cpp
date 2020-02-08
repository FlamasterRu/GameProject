#include "Enemy.h"


Enemy::Enemy()
{

	e_SpeedX = enemySpeedX;
	e_SpeedY = enemySpeedY;
	

	e_Position.x = 0;
	e_Position.y = 0;

	e_MaxPosition.x = 0;
	e_MaxPosition.y = 0;

	e_MinPosition.x = 0;
	e_MinPosition.y = 0;

	e_Health = 1;
	e_Damage = 1;


	// Загрузка текстуры из папки, в которой исполняемый файл
	e_Texture.loadFromFile("hero.jpg");
	e_ptrTexture = &e_Texture;



}





void Enemy::update(float elapsedTime)
{
	e_Position.x += e_SpeedX * elapsedTime;
	e_Position.y += e_SpeedY * elapsedTime;

	changePosition();
}


void Enemy::changePosition()
{
	if (e_Position.x < e_MaxPosition.x)
	{
		e_SpeedX *= -1;    /// Если дошёл до края - разворачиваем моба
	}

	if (e_Position.x > e_MinPosition.x)
	{
		e_SpeedX *= -1;    /// Если дошёл до края - разворачиваем моба
	}

	if (e_Position.y > e_MaxPosition.y)
	{
		///// Поражение.  
		throw("lose");
	}

	e_Convex.setPointCount(11);
	e_Convex.setPoint(0, Vector2f(e_Position.x + 0.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(1, Vector2f(e_Position.x + 1.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(2, Vector2f(e_Position.x + 1.0 * enemyScale, e_Position.y + 0.0 * enemyScale));
	e_Convex.setPoint(3, Vector2f(e_Position.x + 2.0 * enemyScale, e_Position.y + 0.0 * enemyScale));
	e_Convex.setPoint(4, Vector2f(e_Position.x + 2.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(5, Vector2f(e_Position.x + 4.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(6, Vector2f(e_Position.x + 4.0 * enemyScale, e_Position.y + 0.0 * enemyScale));
	e_Convex.setPoint(7, Vector2f(e_Position.x + 5.0 * enemyScale, e_Position.y + 0.0 * enemyScale));
	e_Convex.setPoint(8, Vector2f(e_Position.x + 5.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(9, Vector2f(e_Position.x + 6.0 * enemyScale, e_Position.y + 1.0 * enemyScale));
	e_Convex.setPoint(10, Vector2f(e_Position.x + 3.0 * enemyScale, e_Position.y + 7.0 * enemyScale));



	e_Convex.setTexture(e_ptrTexture);
	e_Convex.setFillColor(Color::Red);
	e_Convex.setPosition(e_Position.x, e_Position.y);

}



ConvexShape Enemy::getEnemyConvex()
{
	return e_Convex;
}




void Enemy::setPositionX(float x)
{
	e_Position.x = x;
}


void Enemy::setPositionY(float y)
{
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


void Enemy::setMaxPositionX(float x)
{
	e_MaxPosition.x = x;
}


void Enemy::setMaxPositionY(float y)
{
	e_MaxPosition.y = y;
}


void Enemy::setMinPositionX(float x)
{
	e_MinPosition.x = x;
}


void Enemy::setMinPositionY(float y)
{
	e_MinPosition.y = y;
}



