//ADD HIGH SCORE, SPEED, LEVEL 3 4 5...// set man hinh gioi thieu// sua lai load level tiep theo//ten nguoi choi/ lua chon ran va fruit(mau sac)
#include "Engine.h"
//using namespace sf;

const Time Engine::TimePerFrame = milliseconds(1.f / 60.f);

Engine::Engine(RenderWindow& game, int& pagenum, Setting& setting) : game(game), pagenum(pagenum), setting(setting) {

    //resolution = Vector2f(800, 600); //man hinh choi
    //.create(VideoMode(800, 600), "Snake Game", Style::Default);

    //pagenum = 100;
    //game.clear();
    game.setFramerateLimit(FPS);

    //mainMenu(window);
    startGame();
    maxLevels = 3;
    name = setting.getName();
    if (name == "") {
        name = "no_name";
    }

    tx3.loadFromFile("../Data/bg_end.png");
    tx2.loadFromFile("../Data/bg_game.png");

    tx1.loadFromFile("../Data/s.png");

    bgEnd.setTexture(tx3);
    bgGame.setTexture(tx2);

    //background.setSize(Vector2f(800, 600));
    //maintexture.loadFromFile("../Data/bg1.jpg");
    //background.setTexture(&maintexture);


        //snake[0].setSize(Vector2f(40, 40));



   // Sprite sprite(tx1);


    eat_sound.loadFromFile("../Data/apple-2.wav");
    sfx.setBuffer(eat_sound);

    gameover_sound.loadFromFile("../Data/dead_sound.ogg");
    sfx1.setBuffer(gameover_sound);

    mainFont.loadFromFile("../Data/Game Shark.otf");
    minorFont.loadFromFile("../Data/DANKI.otf");



    //highscore_end.setString(to_string(highscore));
    setupText(&titleText, mainFont, name, 25, Color::White);
    centerText(titleText, 800, -7);

    // Current Level Text
    setupText(&currentLevelText, mainFont, "Level 1", 25, Color::White);
    currentLevelText.setPosition(Vector2f(15, -7));

    // Score Text

    setupText(&scoreText, mainFont, to_string(scoreThisLevel), 25, Color::White);
    scoreText.setPosition(Vector2f(800 - scoreText.getGlobalBounds().width - 15, -7));

    // Game Over Text
    setupOutlinedText(gameOverText, minorFont, "GAME OVER", 72, Color::Cyan);
    centerText(gameOverText, 800, 50);

    // Game Win Text
    setupOutlinedText(gameWinText, minorFont, "YOU WIN", 72, Color::Cyan);
    centerText(gameWinText, 800, 50);

    // Score End Text
    setupText(&score_end, mainFont, "", 28, Color::Yellow);
    //centerText(score_end, 800, 100);


    //TOP RANKING
    setupOutlinedText(topRankingText, minorFont, "Top ranking", 32, Color(100, 255, 100), Color::Black);
    centerText(topRankingText, 800, 430);

    topRankingBounds = topRankingText.getLocalBounds();

    topRankingBounds.left = 800 / 2 - (topRankingBounds.width) / 2;
    topRankingBounds.top = 430;

    //topRankingBounds.height = 50;
    //topRankingBounds.width = 200;
    /*
    textShape1.setSize((Vector2f(topRankingBounds.width, topRankingBounds.height)));
    textShape1.setFillColor(Color::Cyan);
    textShape1.setPosition(Vector2f(topRankingBounds.left, topRankingBounds.top));
    textShape1.setOutlineColor(Color{ 255,204,0 });
    textShape1.setOutlineThickness(2);
    */

    //TRY AGAIN
    setupOutlinedText(tryAgainText, minorFont, "Try again", 32, Color(100, 255, 100), Color::Black);
    centerText(tryAgainText, 800, 360);

    tryAgainBounds = tryAgainText.getLocalBounds();
    tryAgainBounds.left = 800 / 2 - (tryAgainBounds.width) / 2;
    tryAgainBounds.top = 360;
    //tryAgainBounds.height = 50;
    //tryAgainBounds.width = 200;
    /*
    textShape2.setSize((Vector2f(tryAgainBounds.width , tryAgainBounds.height)));
    textShape2.setFillColor(Color::Cyan);
    textShape2.setPosition(Vector2f(tryAgainBounds.left, tryAgainBounds.top));
    textShape2.setOutlineColor(Color{ 255,204,0 });
    textShape2.setOutlineThickness(2);
    */





    //EXIT
    setupOutlinedText(exitText, minorFont, "Exit", 32, Color(100, 255, 100), Color::Black);
    centerText(exitText, 800, 500);

    exitBounds = exitText.getLocalBounds();

    exitBounds.left = 800 / 2 - exitBounds.width / 2;
    exitBounds.top = 500;

    //exitBounds.height = 50;
    //topRankingBounds.width = 200;
    /*
    textShape3.setSize((Vector2f(exitBounds.width, exitBounds.height)));
    textShape3.setFillColor(Color::Cyan);
    textShape3.setPosition(Vector2f(exitBounds.left, exitBounds.top));
    textShape3.setOutlineColor(Color{ 255,204,0 });
    textShape3.setOutlineThickness(2);
    */


}


void Engine::startGame() {
    speed = setting.getInputSpeed();
    //speed = 3; // cho gamer tu them
    SnakeDir = Direction::DOWN;

    cPoint = 0;
    delay_time = Time::Zero;
    wallSection.clear();
    directQueue.clear();
    scoreThisLevel = 0;
    scoreTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    createSnake();
    appearFruit();
    currentState = GameState::RUN;
    lastState = currentState;
    currentLevelText.setString("level " + to_string(currentLevel));
    // fruitEatText.setString("fruit " + to_string(fruit_EatTotal));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    //fruitEatText.setPosition(
     //   Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, 0));

    scoreText.setString(to_string(scoreThisLevel));

    FloatRect scoreTextBounds = scoreText.getLocalBounds();
}




void Engine::createSnake() {
    snake.clear();

    snake.emplace_back(Vector2f(100, 100));



    snake.emplace_back(Vector2f(100, 80));
    snake.emplace_back(Vector2f(100, 60));
    // snake[0].setTexture(&tx1);
}

void Engine::addSnake() {
    Vector2f newPointpos = snake[snake.size() - 1].getPos();
    snake.emplace_back(newPointpos);
}

void Engine::appearFruit() {
    Vector2f Fruitresolution = Vector2f(800 / 20 - 2, 600 / 20 - 2);
    Vector2f newlocation;
    bool badlocation = false;
    srand(time(nullptr));

    do {
        badlocation = false;
        //create random fruit
        newlocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)Fruitresolution.x) * 20);
        newlocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)Fruitresolution.y) * 20);
        // o trong than ran
        for (auto& s : snake) {
            if (s.getShape().getGlobalBounds().intersects(Rect<float>(newlocation.x, newlocation.y, 20, 20))) {
                badlocation = true;
                break;
            }

        }

        //Check in the wall
        for (auto& w : wallSection) {
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newlocation.x, newlocation.y, 20, 20))) {
                badlocation = true;
                break;
            }
        }

    } while (badlocation);
    fruit.setPos(newlocation);
}

void Engine::togglePause() {
    if (currentState == GameState::RUN) {
        lastState = currentState;
        currentState = GameState::PAUSED;
    }
    else if (currentState == GameState::PAUSED) {
        currentState = lastState;
    }
}


void Engine::checkLevelFiles() {
    ifstream levelsManifest("../Data/levels.txt");
    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);) {
        // Check that we can open the level file
        testFile.open("../Data/levels/" + manifestLine);
        if (testFile.is_open()) {
            // The level file opens, lets add it to the list of available levels
            levels.emplace_back("../Data/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

void Engine::beginNextLevel() {
    // cout << "le";
    currentLevel += 1;
    wallSection.clear();
    directQueue.clear();
    speed += 1;
    SnakeDir = Direction::DOWN;
    cPoint = 0;
    scoreThisLevel = 0;

    loadLevel(currentLevel);
    //createSnake();
    //newSnake();
    appearFruit();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    FloatRect scoreTextBounds = scoreText.getGlobalBounds();

    scoreText.setPosition(Vector2f(800 - scoreTextBounds.width - 15, -7));

}

void Engine::loadLevel(int levelNumber) {
    //cout << "vel";
    levels.push_back("../Data/levels/level1.txt");
    levels.push_back("../Data/levels/level2.txt");
    unsigned int num = levelNumber - 1;
    string levelFile = levels[num];
    //levels.size();
    ifstream level(levelFile);
    string line;
    snake.clear();
    Vector2f newHead;
    vector<Vector2f> newSnakeBody;
    if (level.is_open()) {

        for (int y = 0; y < 30; y++) {
            getline(level, line);
            for (int x = 0; x < 40; x++) {
                if (line[x] == 'x') {
                    wallSection.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
                /*
                else if (line[x] == 'R') {
                    SnakeDir = Direction::RIGHT;
                }
                else if (line[x] == 'D') {
                    SnakeDir = Direction::DOWN;
                }
                else if (line[x] == 'L') {
                    SnakeDir = Direction::LEFT;
                }
                else if (line[x] == 'U') {
                    SnakeDir = Direction::UP;
                }
                */
                //else if (line[x] == 'h') {
                  //  newHead = Vector2f(x * 20, y * 20);
                //}
                //else if (line[x] == 't') {
                  //  newSnakeBody.emplace_back(Vector2f(x, y));
                //}
            }
        }
    }
    level.close();
    createSnake();

    // Build the new snake
    /*
    bool addThisSection ;
    snake.emplace_back(newHead);
   // while (!newSnakeBody.empty()) {
        for (int i = 0; i < newSnakeBody.size();i++) {
            addThisSection = false;
             // Check if this sections is beside last section
            FloatRect snakeBackBounds = snake.back().getShape().getGlobalBounds();
            snakeBackBounds.height = 20;
            snakeBackBounds.width = 20;


            cout << newSnakeBody[i].x << " - " << snake.back().getShape().getGlobalBounds().left / 20<<endl;
            cout << newSnakeBody[i].y << " - " << snake.back().getShape().getGlobalBounds().top / 20 <<endl;
            cout << "------------------";


            if (abs(newSnakeBody[i].x - (snake.back().getShape().getGlobalBounds().left)/20) == 0.5) {
                if (newSnakeBody[i].y == (snake.back().getShape().getGlobalBounds().top / 20)) {
                    addThisSection = true;
                }
            }


            // Check if this section is directly above or below the last section
            else if (abs(newSnakeBody[i].y - (snake.back().getShape().getGlobalBounds().top)/20)  == 0.5) {
                if (newSnakeBody[i].x == (snake.back().getShape().getGlobalBounds().left / 20)) {
                    addThisSection = true;

                }
            }
            // cout << addThisSection;
            if (addThisSection) {

                snake.emplace_back(Vector2f(newSnakeBody[i].x * 20, newSnakeBody[i].y * 20));

                newSnakeBody.erase(newSnakeBody.begin() + i);

                // Đừng tăng i vì một phần tử đã được gỡ bỏ và tất cả các phần tử còn lại đã dịch chuyển lên một vị trí.

            }//else {

                // Chỉ tăng i khi không xóa phần tử để tránh bỏ qua phần tử tiếp theo.

                //i++;

           // }

        }
    //}
    */
}


void Engine::saveScore() {
    loadScore(Topscore); // them tiep vao file Highscore
    highscore.push_back(Player(name, scoreTotal));

    sort(highscore.begin(), highscore.end(), [](const Player& a, const Player& b) {
        return a.scoreP > b.scoreP;
        });

    // Truncate to keep only the top 3 scores
    // 
    // 
    if (highscore.size() > 10) {
        highscore.resize(10);
    }

    ofstream file("../Data/Highscore.txt");
    if (file.is_open()) {
        for (const auto& entry : highscore) {
            file << entry.nameP << " " << entry.scoreP << "\n";
        }


    }
}

void  Engine::loadScore(RenderWindow& Topscore) {
    ifstream file("../Data/Highscore.txt");
    if (file.is_open()) {
        string playerName;
        int playerScore;

        while (file >> playerName >> playerScore) {
            highscore.push_back(Player(playerName, playerScore));
        }



        file.close();
        for (int i = 0; i < 3; i++) {
            const auto& player = highscore;

            //cout << "Player: " << playerName<< ", Score: " << playerScore << std::endl;
            setupText(&topText[i], mainFont, player[i].getName() + " " + to_string(player[i].getScore()), 22, Color{ 255,204,0 });
            FloatRect topTextBounds = topText[i].getLocalBounds();

            topText[i].setPosition(600 / 2 - topTextBounds.width / 2, 150 + 70 * i);


        }
        //topText[0].setPosition(600 / 2 - topTextBounds.width / 2, 110);
        //topText[1].setPosition(110, 200);
        //topText[2].setPosition(380, 250);





    }


    //for (int i = 0; i < 3; i++) {

    //}
}
void Engine::topRanking() {
    RenderWindow Topscore;
    Topscore.create(VideoMode(600, 450), "TOP RANKING", Style::Default);
    while (Topscore.isOpen()) {
        Event event;

        tx2.loadFromFile("../Data/bg_top.png");
        bgTop.setTexture(tx2);




        while (Topscore.pollEvent(event)) {
            if (event.type == Event::Closed) {
                Topscore.close();
                break;
            }
            // cout << loadScore();


        }


        loadScore(Topscore);





        Topscore.draw(bgTop);
        Topscore.draw(topText[0]);
        Topscore.draw(topText[1]);
        Topscore.draw(topText[2]);

        Topscore.display();


        //Topscore.display();



    }

}






void Engine::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);

}


void Engine::Play() {
    Clock clock;

    while (game.isOpen()) {
        Time dt = clock.restart();
        \
            if (currentState == GameState::PAUSED || currentState == GameState::GAMEOVER || currentState == GameState::GAMEWIN) {
                //pause roi an pause tiep se tiep tuc


                Input();
                //ve gameover screen
                if (currentState == GameState::GAMEOVER || currentState == GameState::GAMEWIN) {
                    score_end.setString("Your score is: " + to_string(scoreTotal));
                    centerText(score_end, 800, 150);
                    Draw();

                }
                sleep(milliseconds(2));
                continue;
            }
        delay_time += dt;

        Input();
        Update();
        Draw();


    }
    //game.clear();
    //game.display();

}




// Function to set up text position based on center alignment
void Engine::centerText(Text& text, float screenWidth, float offsetY) {
    FloatRect textBounds = text.getGlobalBounds();
    text.setPosition(Vector2f(screenWidth / 2 - textBounds.width / 2, offsetY));
}

// Function to set up text with outline
void Engine::setupOutlinedText(Text& text, Font& font, const string& content, unsigned int size, Color fillColor, Color outlineColor, float outlineThickness) {
    setupText(&text, font, content, size, fillColor);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
}

string Engine::getName() {
    return name;
}