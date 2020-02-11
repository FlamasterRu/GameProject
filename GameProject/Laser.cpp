#include "Laser.h"


Laser::Laser()
{

	l_Speed.x = laserSpeedX;
	l_Speed.y = laserSpeedY;

	l_Texture.loadFromFile("Laser.png");		/// 8*20 размер в пикселях

	l_Sprite.setTexture(l_Texture);

	l_Damage = 1;

	
	l_Position.x = 0;
	l_Position.y = 0;

}

Laser::Laser(Vector2f position)
{

	l_Speed.x = laserSpeedX;
	l_Speed.y = laserSpeedY;
	l_Texture.loadFromFile("laser.png");		/// 8*20 размер в пикселях

	l_Sprite.setTexture(l_Texture);

	l_Damage = 1;


	l_Position.x = position.x;
	l_Position.y = position.y;

}





void Laser::setSpeed(Vector2f speed)
{
	l_Speed = speed;
}


void Laser::setPosition(Vector2f position)
{
	l_Position = position;
}





Sprite Laser::getLaserSprite()
{
	return l_Sprite;
}


Vector2f Laser::getPosition()
{
	return l_Position;
}







void Laser::update(float elapsedTime)
{
	l_Position.x += l_Speed.x * elapsedTime;
	l_Position.y += l_Speed.y * elapsedTime;

	l_Sprite.setPosition(l_Position);
}



















































