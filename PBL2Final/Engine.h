#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctime>
#include<string>
#include<random>
#include<iomanip>
#include<fstream>
#include <algorithm>
//#include <thread>
#include "Vector.h"
#include<deque>
#include"Menu.h"
#include"Point.h"
#include "Fruit.h"
#include "Wall.h"
#include "Setting.h"


using namespace std;
using namespace sf;



class Engine
{
private:

    //Vector2f resolution;
    //int pagenum;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    RenderWindow& game;
    RenderWindow Topscore;
    int& pagenum;
    Setting& setting;


    vector <Player> highscore;
    float width;
    float height;

    Vector<Point> snake;

    int SnakeDir;

    int speed;
    Time delay_time;

    deque<int> directQueue; // queue cho phim nhan
    int cPoint; //count point
    long long int scoreThisLevel;
    long long int scoreTotal;


    Fruit fruit;
    int currentState;
    int lastState;

    Vector<Wall> wallSection;
    int currentLevel;
    int maxLevels;
    //int numlevel = 5;
    vector<string> levels;

    //Text
    Font mainFont;
    Font minorFont;
    Text titleText;
    //Text fruitEatText;
    Text currentLevelText;
    Text scoreText;
    Text gameOverText;
    Text tryAgainText;
    Text topRankingText;
    Text score_end;
    Text gameWinText;
    //Text nameText;
    Text exitText;
    Text topText[3];

    FloatRect tryAgainBounds;
    FloatRect topRankingBounds;
    FloatRect exitBounds;
    RectangleShape textShape1;
    RectangleShape textShape2;
    RectangleShape textShape3;
    RectangleShape snakeHead;

    Texture tx3;
    Texture tx2;
    Texture tx1;
    Texture tx4;


    Sprite bgEnd;
    Sprite bgGame;
    Sprite bgTop;


    string name;

    //Load apple picture instead of fruit 
    //Texture maintexture;
    //RectangleShape(background);


    //Sound
    sf::SoundBuffer eat_sound;
    Sound sfx;

    sf::SoundBuffer gameover_sound;
    Sound sfx1;
    //FIXXXXXXXXXXXXXX
    const unsigned int targetScore = 100; // de toi level tiep theo
    //int width;
    //int height;



public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUN, PAUSED, GAMEOVER, GAMEWIN };
    Engine(RenderWindow& game, int& pagenum, Setting& setting);
    void Input();

    void Update();
    void Draw();
    //void mainMenu(RenderWindow&);
    void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
    void centerText(Text& text, float screenwidth, float offsetY = 0);
    void setupOutlinedText(Text& text, Font& font, const std::string& content, unsigned int size, Color fillColor, Color outlineColor = Color::Black, float outlineThickness = 2);
    void addDir(int newDir);
    void createSnake();
    void addSnake();
    void appearFruit();
    void checkLevelFiles();
    void loadLevel(int levelNumber);
    void beginNextLevel();
    void  saveScore();
    void loadScore(RenderWindow& Topscore);
    string getName();
    void topRanking();
    //bool checkCollision(Point circle, RectangleShape rectangle);

    void startGame();

    void togglePause();
    // void Game();
    void Play();

};

