#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;


const int enemySpeedX = 50;
const int enemySpeedY = 2;



class Enemy
{
private:

	int e_Health;
	int e_Damage;

	Vector2f e_Position;  //// ���������� ������ �������� ���� ��������������, ������� ��������� ������� �����
	Vector2f e_XRange;   /// ����������, � ������� ��� ���������������
	Vector2f e_YRange;


	Sprite e_Sprite;

	Texture e_Texture;


	Vector2f e_Speed;   // �������� �������� � �������� � ������� �� ��� �
					   // �������� �������� � �������� � ������� �� ��� Y


public:


	Enemy();




	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	void setHealth(int health);
	void setDamage(int damage);
	void setXRange(Vector2f xRange);
	void setXRange(float xLeft, float xRight);
	void setYRange(Vector2f yRange);
	void setYRange(float yLeft, float yRight);


	Vector2f getPosition();
	Sprite getEnemySprite();


	int update(float elapsedTime);  	// ��� ������� ����� ���������� �� ������ ����

};

