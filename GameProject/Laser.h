#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

const float laserSpeedX = -0;
const float laserSpeedY = -50;    /// ��� ��� ������ ��������� � ����� ������� ����, �� ����� ������ ����� ���� ��������� ���������� 



class Laser
{

private:

	Vector2f l_speed;    // �������� �� ���� � � y

	Texture l_Texture;

	Sprite l_sprite;

	int l_damage;

	Vector2f l_coordinates[2];      //// ���������� ������� ��������� �������������� ������������ �����





public:

	Laser();

	void setSpeed(Vector2f speed);

	void changePosition();

	Sprite getLaserSprite();

	void update(float elapsedTime);






};




































