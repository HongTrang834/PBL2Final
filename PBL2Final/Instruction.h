#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include"Vector.h"
#include<iostream>
#include<fstream>
#include <sstream>
//#include"Menu.h"

using namespace std;
using namespace sf;



class Instruction {
private:
	RenderWindow& game;
	Sprite directKey;
	Text instructionText;

	Font font;
	int& pagenum;

	Texture tx1;
	Texture tx2;
	Texture tx3;
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;


	Texture backgroundMenu;
	Sprite bg;


public:
	Instruction(RenderWindow& game, int& pagenum);
	void Show();
	//void Speed();
	void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
	//int getInputSpeed();
	//void Name();
	//string getName();
	//void Alert();
	//bool isPlayerExist(const vector<Player>& players, const string& playerName);
};