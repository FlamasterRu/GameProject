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

	Vector2f e_Position;  //// ���������� ������ �������� ���� ��������������, ������� ��������� ������� �����
	Vector2f e_MaxPosition;   /// ����������, � ������� ��� ���������������
	Vector2f e_MinPosition;


	ConvexShape e_Convex;

	Texture e_Texture;
	const Texture* e_ptrTexture;

	float e_SpeedX;   // �������� �������� � �������� � ������� �� ��� �
	float e_SpeedY;   // �������� �������� � �������� � ������� �� ��� Y


public:

	static int e_Number;     /// ���������� ������ �� ������

	Enemy();


	void changePosition();   /// ����������� � ��������� ������ e_Convex

	ConvexShape getEnemyConvex();


	// ��� ������� ����� ���������� �� ������ ����
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

