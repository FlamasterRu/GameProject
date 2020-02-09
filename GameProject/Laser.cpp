#include "Laser.h"


Laser::Laser()
{

	l_speed.x = laserSpeedX;
	l_speed.y = laserSpeedY;

	l_Texture.loadFromFile("laser.png");

	l_sprite.setTexture(l_Texture);

	l_damage = 1;

	Vector2u temp = l_Texture.getSize();
	
	l_coordinates[0].x = 0;
	l_coordinates[0].y = 0;
	l_coordinates[1].x = temp.x;
	l_coordinates[1].y = temp.y;

}


void Laser::setSpeed(Vector2f speed)
{
	l_speed.x = speed.x;
	l_speed.y = speed.y;
}


void Laser::changePosition()
{
	l_sprite.setPosition(l_coordinates[0]);
}

void Laser::update(float elapsedTime)
{
	l_coordinates[0].x += l_speed.x * elapsedTime;
	l_coordinates[0].y += l_speed.y * elapsedTime;

	changePosition();
}


Sprite Laser::getLaserSprite()
{
	return l_sprite;
}



















































