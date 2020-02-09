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

	ContextSettings m_Setting;   /// для сглаживания 

	Sprite m_BackgroundSprite;

	Texture m_BackgroundTexture;

	Hero m_Hero;
	Enemy* e_Enemy;



	void input();
	void update(float dtAsSeconds, Clock clock);
	void draw();

public:

	Engine();
	~Engine();

	// Функция старт вызовет все приватные функции
	void start();

	void check();

};