#include "Hero.h"

Hero::Hero()
{
	// Вписываем в переменную скорость
	m_Speed = speedHero;

	// Связываем текстуру и спрайт
	m_Texture.loadFromFile("hero.jpg");

	m_ptrTexture = &m_Texture;

	

	// Устанавливаем начальную позицию Боба в пикселях
	m_Position.x = 200;
	m_Position.y = 200;

	m_BotPressed = false;
	m_TopPressed = false;
	m_LeftPressed = false;
	m_RightPressed = false;

}


void Hero::changePosition()
{
	m_convex.setPointCount(13);
	m_convex.setPoint(0, Vector2f(m_Position.x + 0.0 * heroScale, m_Position.y + 10.0 * heroScale));
	m_convex.setPoint(1, Vector2f(m_Position.x + 0.0 * heroScale, m_Position.y + 8.0 * heroScale));
	m_convex.setPoint(2, Vector2f(m_Position.x + 3.0 * heroScale, m_Position.y + 0.0 * heroScale));
	m_convex.setPoint(3, Vector2f(m_Position.x + 3.0 * heroScale, m_Position.y + 5.0 * heroScale));
	m_convex.setPoint(4, Vector2f(m_Position.x + 3.5 * heroScale, m_Position.y + 6.0 * heroScale));
	m_convex.setPoint(5, Vector2f(m_Position.x + 4.0 * heroScale, m_Position.y + 5.0 * heroScale));
	m_convex.setPoint(6, Vector2f(m_Position.x + 4.0 * heroScale, m_Position.y + 0.0 * heroScale));
	m_convex.setPoint(7, Vector2f(m_Position.x + 7.0 * heroScale, m_Position.y + 8.0 * heroScale));
	m_convex.setPoint(8, Vector2f(m_Position.x + 7.0 * heroScale, m_Position.y + 10.0 * heroScale));
	m_convex.setPoint(9, Vector2f(m_Position.x + 5.0 * heroScale, m_Position.y + 10.0 * heroScale));
	m_convex.setPoint(10, Vector2f(m_Position.x + 5.0 * heroScale, m_Position.y + 9.0 * heroScale));
	m_convex.setPoint(11, Vector2f(m_Position.x + 2.0 * heroScale, m_Position.y + 9.0 * heroScale));
	m_convex.setPoint(12, Vector2f(m_Position.x + 2.0 * heroScale, m_Position.y + 10.0 * heroScale));


	m_convex.setTexture(m_ptrTexture);
	m_convex.setFillColor(Color::White);
	m_convex.setPosition(m_Position.x, m_Position.y);
}


ConvexShape Hero::getHeroConvex()
{
	return m_convex;
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

// Двигаем на основании пользовательского ввода в этом кадре, прошедшего времени и скорости
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

	// перемещаем фигуру героя
	changePosition();

}