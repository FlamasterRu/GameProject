#pragma once
#include <SFML/Graphics.hpp>
#include "Laser.h"

const int heroSpeed = 400;
const int numLaser = 50;    /// ������������ ���������� ������� �� ������


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// ���������� ������ �������� ���� ��������������, ������� ��������� ������� �����

	Sprite m_Sprite;

	Texture m_Texture;

	Laser* m_laser[numLaser];

	int m_Health;

	// ���������� ���������� ��� ������������ ����������� ��������
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;
	bool m_GoFire;

	// �������� � �������� � �������
	float m_Speed;

	float m_LastFire;


public:

	Hero();
	~Hero();


	// ��� ��������
	void moveLeft();
	void moveRight();
	void moveTop();
	void moveBot();


	// ����������� ��������
	void stopLeft();
	void stopRight();
	void stopTop();
	void stopBot();

	// ��� ��������
	void goFire();
	void stopFire();


	void setLaserNullptr(int num);


	Sprite getHeroSprite();
	Laser* getLaser(int num);


	// ��� ������� ����� ���������� �� ������ ����
	void update(float elapsedTime);

	void fire();

};