#include "Engine.h"

void Engine::Update() {
    //Update position
    if (delay_time.asMilliseconds() >= milliseconds(100.f / float(speed)).asMilliseconds()) {
        FloatRect lastPointRect = snake.front().getShape().getGlobalBounds();
        Vector2f thisPointPos = snake[0].getPos();
        Vector2f lastPointPos = thisPointPos;
        bool gameWinactive = false;

        if (!directQueue.empty()) {
            // Giup khong bi xung dot luc di chuyen
            switch (SnakeDir) {
            case Direction::UP:
                if (directQueue.front() != Direction::DOWN) {
                    SnakeDir = directQueue.front();
                }
                break;
            case Direction::DOWN:
                if (directQueue.front() != Direction::UP) {
                    SnakeDir = directQueue.front();
                }
                break;
            case Direction::RIGHT:
                if (directQueue.front() != Direction::LEFT) {
                    SnakeDir = directQueue.front();
                }
                break;
            case Direction::LEFT:
                if (directQueue.front() != Direction::RIGHT) {
                    SnakeDir = directQueue.front();
                }
                break;
            }
            directQueue.pop_front();
        }


        //
        if (cPoint) {
            addSnake();
            cPoint--;
        }
        //Update head snake
        switch (SnakeDir) {
        case Direction::RIGHT:
        {
            snake[0].setRotation(270.f);

            snake[0].setPos(Vector2f(thisPointPos.x + 20, thisPointPos.y));

            break;
        }
        case Direction::DOWN:
            snake[0].setRotation(0.f);

            snake[0].setPos(Vector2f(thisPointPos.x, thisPointPos.y + 20));
            break;
        case Direction::LEFT:
            snake[0].setRotation(90.f);

            snake[0].setPos(Vector2f(thisPointPos.x - 20, thisPointPos.y));
            break;
        case Direction::UP:
            snake[0].setRotation(180.f);

            snake[0].setPos(Vector2f(thisPointPos.x, thisPointPos.y - 20));
            break;
        }


        //Update tail snake
        for (int i = 1; i < snake.size(); i++) {
            lastPointRect = snake[i].getShape().getGlobalBounds();
            thisPointPos = snake[i].getPos();
            snake[i].setPos(lastPointPos);
            lastPointPos = thisPointPos;
        }
        //run snake point update functions
        for (auto& s : snake) {
            s.update();
        }
        //eat fruit - add Point to snake
        FloatRect headBounds = snake[0].getShape().getGlobalBounds();
        headBounds.height = 20;
        headBounds.width = 20;
        FloatRect fruitBounds = fruit.getSprite().getGlobalBounds();
        fruitBounds.height = 20;
        fruitBounds.width = 20;

        if (headBounds.intersects(fruitBounds)) {
            // snake[0].getShape().getGlobalBounds().height = 1;

            // sleep(seconds(2));
             // fruit_EatThisLevel += 1;
              //fruit_EatTotal += 1;
            scoreThisLevel += 10;
            scoreTotal += 10;
            scoreText.setString(to_string(scoreThisLevel));
            FloatRect scoreTextBounds = scoreText.getLocalBounds();
            scoreText.setPosition(Vector2f(800 - scoreTextBounds.width - 15, -7));
            //fruitEatText.setString("fruit" + to_string(fruit_EatTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            //fruitEatText.setPosition(
                //Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, 0));
            //cPoint += 1;
            //speed++;
            //appearFruit();
            sfx.play();
            bool beginnewLevel = true;
            if (scoreThisLevel == targetScore) {
                if (currentLevel < maxLevels) {
                    beginnewLevel = true;
                    beginNextLevel();
                }
                if (currentLevel == maxLevels) {
                    //beginnewLevel = false;
                    currentState = GameState::GAMEWIN;
                    saveScore();

                    gameWinactive = true;


                }


            }
            if (beginnewLevel) {
                cPoint += 2;
                appearFruit();

            }
        }


        //ran cham than thi game over
        for (int i = 1; i < snake.size(); i++) {
            if (headBounds.intersects(snake[i].getShape().getGlobalBounds())) {
                //game over
                currentState = GameState::GAMEOVER;
                saveScore();
                cout << "thansave";

                sfx1.play();
                break;


            }
        }

        // ran cham tuong thi game over

        for (auto& w : wallSection) {
            FloatRect wallBounds = w.getShape().getGlobalBounds();
            wallBounds.height = 20;
            wallBounds.width = 20;

            if (headBounds.intersects(wallBounds)) {
                if (!gameWinactive) {
                    currentState = GameState::GAMEOVER;
                    saveScore();
                    sfx1.play();
                    break;

                }
            }
        }


        delay_time = Time::Zero;
        //updateCurrentBest 
        //FIXXXXXXXXXXXXXXXXXXXXXXXX
        //highscore = 0;

        //if (scoreTotal > highscore) highscore = scoreTotal;

        //if (currentLevel == maxLevels) {
           // currentState = GameState::GAMEWIN;
       // }
    }

}