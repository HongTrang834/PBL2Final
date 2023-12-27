#include "Engine.h"
void Engine::Input() {

    Event event;
    while (game.pollEvent(event)) {
        // Window closed

        if (event.type == Event::Closed) {
            game.close();
        }

        // Handle Keyboard Input
        if (event.type == Event::KeyPressed) {
            // Stop 
            if (event.key.code == Keyboard::X) {
                currentState = GAMEOVER;
            }

            // Pause
            if (event.key.code == Keyboard::Space) {
                togglePause();
            }

            // Direction
            if (event.key.code == Keyboard::Up) {
                addDir(Direction::UP);
            }
            else if (event.key.code == Keyboard::Down) {
                addDir(Direction::DOWN);
            }
            else if (event.key.code == Keyboard::Left) {
                addDir(Direction::LEFT);
            }
            else if (event.key.code == Keyboard::Right) {
                addDir(Direction::RIGHT);
            }

        }
        // New Game
        if (event.type == Event::MouseButtonPressed) {
            if (currentState == GameState::GAMEOVER || currentState == GameState::GAMEWIN) {
                if (event.mouseButton.button == Mouse::Button::Left) {
                    Vector2i mousePosition = Mouse::getPosition(game);
                    if (tryAgainBounds.contains(Vector2f(mousePosition))) {
                        game.close();
                        Menu menu(800, 600);
                        menu.runMenu();


                    }
                    if (topRankingBounds.contains(Vector2f(mousePosition))) {
                        topRanking();
                    }
                    if (exitBounds.contains(Vector2f(mousePosition))) {
                        game.close();
                    }
                }
            }
        }
    }
}


void Engine::addDir(int newDir) {
    if (directQueue.empty()) {
        directQueue.emplace_back(newDir);
    }
    else {
        if (directQueue.back() != newDir) {
            directQueue.emplace_back(newDir);
        }
    }
}
