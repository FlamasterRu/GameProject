#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h";

using namespace sf;

class Engine
{
private:

	RenderWindow m_Window;

	ContextSettings m_Setting;

	Sprite m_BackgroundSprite;

	Texture m_BackgroundTexture;

	Hero m_Hero;



	void input();
	void update(float dtAsSeconds);
	void draw();

public:

	Engine();

	// Функция старт вызовет все приватные функции
	void start();

};