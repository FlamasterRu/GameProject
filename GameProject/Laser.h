#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

const float laserSpeedX = -0;
const float laserSpeedY = -50;    /// так как начало координат в левом верхнем углу, то чтобы лететь вверх надо уменьшать координату 



class Laser
{

private:

	Vector2f l_speed;    // скорость по осям х и y

	Texture l_Texture;

	Sprite l_sprite;

	int l_damage;

	Vector2f l_coordinates[2];      //// координаты главной диагонали прямоугольника описывающего лазер





public:

	Laser();

	void setSpeed(Vector2f speed);

	void changePosition();

	Sprite getLaserSprite();

	void update(float elapsedTime);






};




































