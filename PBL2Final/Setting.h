#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include"Vector.h"
#include<iostream>
#include<fstream>
//#include"Menu.h"

using namespace std;
using namespace sf;

struct Player {
	string nameP;
	int scoreP;
	Player() : nameP(""), scoreP(0) {}
	// Constructor for convenience
	Player(const std::string& n, int s) : nameP(n), scoreP(s) {}
	string getName() const {
		return this->nameP;
	}
	int getScore() const {
		return this->scoreP;
	}
};

class Setting {
private:
	RenderWindow& game;
	string speed;
	int& pagenum;
	string name;

	int inputSpeed;
	Text enterSpeedText;
	Text speedText;
	Font font;
	Font alertFont;

	Texture tx2;
	Texture tx3;

	Sprite sprite2;
	Sprite sprite3;

	int inputName;
	Text enterNameText;
	Text nameText;
	Text alertText;

	Texture backgroundMenu;
	Sprite bg;


public:
	Setting(RenderWindow& game, int& pagenum);
	void Speed();
	void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
	int getInputSpeed();
	void Name();
	string getName();
	void Alert();
	bool isPlayerExist(const vector<Player>& players, const string& playerName);
};