#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Enemy.h"

/// + координаты верхнего левого угла кнопки и левого нижнего
enum userInput
{
	Exit,			// Выйти из игры 0     (910, 640)   (1030, 700)
	StartGame,		// Начать игру 1		(850, 410) (1110, 480)
	OpenSetting,	// Открыть настройки игры 2		(890, 540)  (1070, 600)
	ShowMenu		// Отобразить меню 3
};


const int numEnemy = 1;
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
	Enemy* m_Enemy[numEnemy * lineEnemy];

	int m_NumberAliveEnemy;

	int m_userMenuInput;

	bool m_changeWindow;



	void input();
	void update(float dtAsSeconds);
	void draw();
	void check();

public:

	Engine();
	~Engine();

	// Функция старт вызовет все приватные функции
	void start();

	void menu();

	void setting();

	int getUserMenuInput();

};