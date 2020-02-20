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


const int numEnemy = 10;
const int lineEnemy = 3;
const Time timeDelayEscape = seconds(0.3);   // чтобы сразу не выключить игру, так как пользователь не моментально отпускает кнопку Esc


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


	// Кнопки управления
	Keyboard::Key keyToMoveRight;
	Keyboard::Key keyToMoveLeft;
	Keyboard::Key keyToMoveTop;
	Keyboard::Key keyToMoveBot;
	Keyboard::Key keyToFire;




	void input();
	void inputInGame();
	void inputInMenu();
	void inputInSetting();
	void update(float dtAsSeconds);
	void updateGameWindow(float dtAsSeconds);
	void updateMenuWindow(float dtAsSeconds);
	void updateSettingWindow(float dtAsSeconds);
	void draw();
	void drawGame();
	void drawMenu();
	void drawSetting();
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