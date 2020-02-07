#pragma once
#include <SFML/Graphics.hpp>

const float heroScale = 10.0;
const int speedHero = 300;


using namespace sf;

class Hero
{

private:

	Vector2f m_Position;  //// ���������� ������ �������� ���� ��������������, ������� ��������� ������� �����

	ConvexShape m_convex;

	Texture m_Texture;
	const Texture* m_ptrTexture;

	// ���������� ���������� ��� ������������ ����������� ��������
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;

	// �������� � �������� � �������
	float m_Speed;


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
	void update(float elapsedTime);

	/// ���������� ������ �����
	void changePosition();

	ConvexShape getHeroConvex();

};