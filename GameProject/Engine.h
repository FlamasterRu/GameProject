#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Enemy.h"

/// + ���������� �������� ������ ���� ������ � ������ �������
enum userInput
{
	Exit,			// ����� �� ���� 0     (910, 640)   (1030, 700)
	StartGame,		// ������ ���� 1		(850, 410) (1110, 480)
	OpenSetting,	// ������� ��������� ���� 2		(890, 540)  (1070, 600)
	ShowMenu		// ���������� ���� 3
};


const int numEnemy = 10;
const int lineEnemy = 3;
const Time timeDelayEscape = seconds(0.3);   // ����� ����� �� ��������� ����, ��� ��� ������������ �� ����������� ��������� ������ Esc


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

	int m_userMenuInput;

	bool m_changeWindow;


	// ������ ����������
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

	// ������� ����� ������� ��� ��������� �������
	void start();

	void menu();

	void setting();

	int getUserMenuInput();

};