#pragma once
#include <SFML/Graphics.hpp>
#include "Setting.h"
#include"Engine.h"
#include "Instruction.h"
//#include "Start.h"

using namespace std;
using namespace sf;

#define Max_menu 4

class Menu
{
public:
	//int selected;

	Font mainFont;
	FloatRect mainMenuTextBounds[Max_menu];
	RenderWindow game;

public:
	Text mainMenuText[Max_menu];

	Menu(float width, float height);
	void DrawMenu();
	//void MoveUp();
	//void MoveDown();
	//void setSelected(int n);
	//int pressed();
	void runMenu();
	void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
	~Menu();

};

