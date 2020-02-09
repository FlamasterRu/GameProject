#pragma once
#include <SFML/Graphics.hpp>
#include "Laser.h"

const float heroScale = 10.0;
const int heroSpeed = 300;
const int numLaser = 1000;    /// ������������ ���������� ������� �� ������


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// ���������� ������ �������� ���� ��������������, ������� ��������� ������� �����

	ConvexShape m_convex;

	Texture m_Texture;
	const Texture* m_ptrTexture;

	Laser* m_laser[numLaser];

	int m_health;

	// ���������� ���������� ��� ������������ ����������� ��������
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;
	bool m_GoFire;

	// �������� � �������� � �������
	float m_Speed;

	float m_lastFire;


public:

	Hero();


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

	// ��� ������� ����� ���������� �� ������ ����
	void update(float elapsedTime, Clock clock);

	/// ���������� ������ �����
	void changePosition();

	ConvexShape getHeroConvex();

	void fire();

	Laser* getLaser(int num);

	void goFire();
	
	void stopFire();

};