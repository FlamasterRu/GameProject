#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;


const float enemyScale = 10.0;
const int enemySpeedX = 50;
const int enemySpeedY = 2;



class Enemy
{
private:

	int e_Health;
	int e_Damage;

	Vector2f e_Position;  ////  оординаты левого верхнего угла примоугольника, который описывает фигурку врага
	Vector2f e_MaxPosition;   /// координаты, в которых моб разворачиваетс€
	Vector2f e_MinPosition;


	ConvexShape e_Convex;

	Texture e_Texture;
	const Texture* e_ptrTexture;

	float e_SpeedX;   // скорость движени€ в пиксел€х в секунду по оси ’
	float e_SpeedY;   // скорость движени€ в пиксел€х в секунду по оси Y


public:

	static int e_Number;     /// количество врагов на экране

	Enemy();


	void changePosition();   /// перемещение и изменение фигуры e_Convex

	ConvexShape getEnemyConvex();


	// Ёта функци€ будет вызыватьс€ на каждый кадр
	void update(float elapsedTime);


	void setPositionX(float x);

	void setPositionY(float y);

	void setHealth(int health);

	void setDamage(int damage);

	void setMaxPositionX(float x);

	void setMaxPositionY(float y);

	void setMinPositionX(float x);

	void setMinPositionY(float y);
};

