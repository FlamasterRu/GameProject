#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;


const int enemySpeedX = 90;
const int enemySpeedY = 8;



class Enemy
{
private:

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
	void setXRange(Vector2f xRange);
	void setXRange(float xLeft, float xRight);
	void setYRange(Vector2f yRange);
	void setYRange(float yLeft, float yRight);


	Vector2f getPosition();
	Sprite getEnemySprite();


	void update(float elapsedTime);  	// ��� ������� ����� ���������� �� ������ ����

};

