#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Point {
private:
    Vector2f pos;
    RectangleShape point;
    Vector2f size;
    //Texture tx_snake;
public:
    Point();
    explicit Point(Vector2f startPos);

    Vector2f getPos();
    void setPos(Vector2f newPos);
    RectangleShape getShape();


    void update();
    void setTexture(sf::Texture* texture);

    void setSize(Vector2f size);
    void setRotation(float angle);


};

