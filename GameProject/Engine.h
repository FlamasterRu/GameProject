#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h";
#include "Enemy.h"





const int numEnemy = 10;
const int lineEnemy = 3;


using namespace sf;

class Engine
{
private:

	RenderWindow m_Window;

	ContextSettings m_Setting;   /// ��� ����������� 

	Sprite m_BackgroundSprite;

	Texture m_BackgroundTexture;

	Hero m_Hero;
	Enemy* m_Enemy[numEnemy * lineEnemy];

	int m_NumberAliveEnemy;



	void input();
	void update(float dtAsSeconds);
	void draw();
	void check();

public:

	Engine();
	~Engine();

	// ������� ����� ������� ��� ��������� �������
	void start();

};