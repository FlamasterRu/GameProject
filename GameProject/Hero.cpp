#include "Hero.h"

Hero::Hero()
{
	// ��������� � ���������� ��������
	m_Speed = heroSpeed;

	// �������� �������� �� �����, � ������� ����������� ����
	m_Texture.loadFromFile("Hero.png");    ////  70*100 ������ � ��������

	m_Sprite.setTexture(m_Texture);


	for (int i = 0; i < numLaser; ++i)
	{
		m_laser[i] = nullptr;
	}

	// ������������� ��������� ������� � ��������
	m_Position.x = 925;
	m_Position.y = 800;

	m_BotPressed = false;
	m_TopPressed = false;
	m_LeftPressed = false;
	m_RightPressed = false;
	m_GoFire = false;

	m_LastFire = 1000.0;

	m_Health = 3;

}

Hero::~Hero()
{
	for (int i = 0; i < numLaser; ++i)
	{
		if (m_laser[i] != nullptr)
		{
			delete m_laser[i];
		}
	}
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





void Hero::setLaserNullptr(int num)
{
	m_laser[num] = nullptr;
}





Sprite Hero::getHeroSprite()
{
	return m_Sprite;
}


Laser* Hero::getLaser(int num)
{
	return m_laser[num];
}










// ������� �� ��������� ����������������� ����� � ���� �����, ���������� ������� � ��������
void Hero::update(float elapsedTime)
{
	float maxX = VideoMode::getDesktopMode().width;     ///// �� ���� ������ �� ����������� ������� � ������� �� ��� ������
	float maxY = VideoMode::getDesktopMode().height;
	maxX -= m_Texture.getSize().x;
	maxY -= m_Texture.getSize().y;
	if (m_RightPressed)
	{
		if (m_Position.x + m_Speed * elapsedTime < maxX)    	// ����� �� ������� �� ������� ��������. ����������� ������, ������� ������������ ���������� � 2 ���� ������ ���������� ������
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
		if (m_Position.y - m_Speed * elapsedTime > 650)
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

	m_LastFire += elapsedTime;
	if (m_GoFire)
	{
		if (m_LastFire > 1.0)    /// �������, ������� ������ ������ � ���������� ��������, ����� ������� ����� �� ��������
		{
			fire();
			m_LastFire = 0;
		}
	}

	// ���������� ������ �����
	m_Sprite.setPosition(m_Position);
}



void Hero::fire()
{
	int freeLaser = 0, i;
	for (i = 0; i < numLaser; ++i)
	{
		if (m_laser[i] == nullptr)
		{
			++freeLaser;                  //////////////////// ������� ������� ��������� ����� ������� �� ������������ ������ �������
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
		temp.y = m_Position.y;
		m_laser[i] = new Laser();
		temp.x = m_Position.x + m_Texture.getSize().x / 2 - m_laser[i]->getLaserSprite().getTexture()->getSize().x / 2;
		temp.y = m_Position.y - m_laser[i]->getLaserSprite().getTexture()->getSize().y;
		m_laser[i]->setPosition(temp);
	}

}


















