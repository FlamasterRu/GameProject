#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

const float laserSpeedX = -0;
const float laserSpeedY = -450;    /// так как начало координат в левом верхнем углу, то чтобы лететь вверх надо уменьшать координату 



class Laser
{

private:

	Vector2f l_Speed;    // скорость по осям х и y

	Texture l_Texture;

	Sprite l_Sprite;

	int l_Damage;

	Vector2f l_Position;      //// координаты главной диагонали прямоугольника описывающего лазер





public:

	Laser();
	Laser(Vector2f position);



	void setSpeed(Vector2f speed);
	void setPosition(Vector2f position);



	Sprite getLaserSprite();
	Vector2f getPosition();



	void update(float elapsedTime);

};




































