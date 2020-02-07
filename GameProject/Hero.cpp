#include "Hero.h"

Hero::Hero()
{
	// ��������� � ���������� �������� ����
	m_Speed = 400;

	// ��������� �������� � ������
	m_Texture.loadFromFile("hero.png");
	m_Sprite.setTexture(m_Texture);

	

	// ������������� ��������� ������� ���� � ��������
	m_Position.x = 960;
	m_Position.y = 800;

	m_BotPressed = false;
	m_TopPressed = false;
	m_LeftPressed = false;
	m_RightPressed = false;

}


Sprite Hero::getSprite()
{
	return m_Sprite;
}

void Hero::moveLeft()
{
	m_LeftPressed = true;
}

void Hero::moveRight()
{
	m_RightPressed = true;
}

void Hero::moveTop()
{
	m_TopPressed = true;
}

void Hero::moveBot()
{
	m_BotPressed = true;
}

void Hero::stopLeft()
{
	m_LeftPressed = false;
}

void Hero::stopRight()
{
	m_RightPressed = false;
}

void Hero::stopTop()
{
	m_TopPressed = false;
}

void Hero::stopBot()
{
	m_BotPressed = false;
}

// ������� �� ��������� ����������������� ����� � ���� �����, ���������� ������� � ��������
void Hero::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (m_TopPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_BotPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	// �������� ������ �� ����� �������
	m_Sprite.setPosition(m_Position);

}