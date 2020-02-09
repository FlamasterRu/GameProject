#include "Hero.h"

Hero::Hero()
{
	// ¬писываем в переменную скорость
	m_Speed = heroSpeed;

	// «агрузка текстуры из папки, в которой исполн€емый файл
	m_Texture.loadFromFile("hero.jpg");

	m_ptrTexture = &m_Texture;

	for (int i = 0; i < numLaser; ++i)
	{
		m_laser[i] = nullptr;
	}

	// ”станавливаем начальную позицию в пиксел€х
	m_Position.x = 450;
	m_Position.y = 400;

	m_BotPressed = false;
	m_TopPressed = false;
	m_LeftPressed = false;
	m_RightPressed = false;
	m_GoFire = false;

	m_lastFire = 10.0;
	
	m_health = 3;

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
	m_convex.setFillColor(Color(255, 150, 0));
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

void Hero::goFire()
{
	m_GoFire = true;
}

void Hero::stopFire()
{
	m_GoFire = false;
}

// ƒвигаем на основании пользовательского ввода в этом кадре, прошедшего времени и скорости
void Hero::update(float elapsedTime, Clock clock)
{
	float maxX = VideoMode::getDesktopMode().width / 2.07;     ///// не знаю почему но фактические размеры в столько то раз меньше
	float maxY = VideoMode::getDesktopMode().height / 2.2;

	if (m_RightPressed)
	{
		if (m_Position.x + m_Speed * elapsedTime < maxX)    	// „тобы не выходил за пределы монитора. ‘актический размер, который отрисовывает библиотека в 2 раза меньше разрешени€ экрана

		{
			m_Position.x += m_Speed * elapsedTime;
		}
	}

	if (m_LeftPressed)
	{
		if (m_Position.x - m_Speed * elapsedTime > 0)
		{
			m_Position.x -= m_Speed * elapsedTime;
		}
	}

	if (m_TopPressed)
	{
		if (m_Position.y - m_Speed * elapsedTime > 290)
		{
			m_Position.y -= m_Speed * elapsedTime;
		}
	}

	if (m_BotPressed)
	{
		if (m_Position.y + m_Speed * elapsedTime < maxY)
		{
			m_Position.y += m_Speed * elapsedTime;
		}
	}

	m_lastFire += elapsedTime;
	if (m_GoFire)
	{
		if (m_lastFire > 1.0)
		{
			fire();
			m_lastFire = 0;
		}
	}

	// перемещаем фигуру геро€
	changePosition();



}



void Hero::fire()
{
	int freeLaser = 0, i = 0;
	for (i = 0; i < numLaser; ++i)
	{
		if (m_laser[i] == nullptr)
		{
			++freeLaser;                  //////////////////// считаем сколько выстрелов можно сделать до переполнени€ буфера лазеров
		}
	}
	if (freeLaser <= 0)
	{
		throw("End laser buffer");
	}
	else
	{
		for (i = 0; m_laser[i] != nullptr; ++i);
		Vector2f temp;
		temp.x = m_Position.x*2 + 3.1 * heroScale;
		temp.y = m_Position.y*2;
		m_laser[i] = new Laser(temp);
		temp.y = m_Position.y * 2 - m_laser[i]->getLaserSprite().getTexture()->getSize().y;
		m_laser[i]->setPosition(temp);
	}

}






Laser* Hero::getLaser(int num)
{
	return m_laser[num];
}














