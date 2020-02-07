#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hero
{

private:

	Vector2f m_Position;

	Sprite m_Sprite;

	Texture m_Texture;

	// ���������� ���������� ��� ������������ ����������� ��������
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_TopPressed;
	bool m_BotPressed;

	// �������� � �������� � �������
	float m_Speed;


public:

	Hero();

	// ��� �������� ������� � ������� �������
	Sprite getSprite();

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

};