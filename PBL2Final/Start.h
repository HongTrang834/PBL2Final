#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include"Menu.h"

using namespace sf;
using namespace std;

class Start
{
public:
	RenderWindow window;
	Texture backgroundMain;
	Sprite bgMain;
	//RenderWindow& game;
	//Menu& menu;
public:
	//Start( Menu& menu);
	void starttheGame();
	void loadingBar();
};

