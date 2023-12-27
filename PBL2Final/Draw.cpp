#pragma once
#include "Engine.h"

void Engine::Draw() {
    if (game.isOpen()) {
        game.draw(bgGame);
        //draw wall
        for (auto& w : wallSection) {
            Texture tx_wall;
            tx_wall.loadFromFile("../Data/wall.png");


            w.setTexture(&tx_wall);


            game.draw(w.getShape());
        }

        //draw fruit

        game.draw(fruit.getSprite());

        //draw snake point
        for (auto& s : snake) {
            if (&s == &snake[0]) {

                tx4.loadFromFile("../Data/snake.png");
                snake[0].setTexture(&tx4);
                game.draw(snake[0].getShape());

            }
            else {
                s.setTexture(&tx1);
                game.draw(s.getShape());
            }

        }



        //draw game
        if (currentState == GameState::RUN || currentState == GameState::PAUSED) {
            game.draw(titleText);
            game.draw(currentLevelText);
            game.draw(scoreText);
        }
        //Gameover 

        if (currentState == GameState::GAMEOVER) {
            game.clear();
            game.draw(bgEnd);
            game.draw(gameOverText);


            game.draw(tryAgainText);
            game.draw(topRankingText);
            game.draw(exitText);
            //game.draw(nameText);
            game.draw(score_end);

        }
        //Game win
        if (currentState == GameState::GAMEWIN) {
            game.clear();
            game.draw(bgEnd);
            game.draw(gameWinText);

            game.draw(tryAgainText);
            game.draw(topRankingText);
            game.draw(exitText);
            //game.draw(nameText);
            game.draw(score_end);
        }

        game.display();
    }
}


