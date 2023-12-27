#include "Point.h"
Point::Point() {}
Point::Point(Vector2f startPos) {
    point.setSize(Vector2f(20, 20));
    point.setFillColor(Color::White);
    point.setOrigin(10.f, 10.f);
    point.setPosition(startPos);
    pos = startPos;

}

Vector2f  Point::getPos() {
    return pos;
}

void Point::setPos(Vector2f newPos) {
    pos = newPos;
}

RectangleShape Point::getShape() {
    return point;
}

void Point::update() {
    point.setPosition(pos);
}
void Point::setTexture(sf::Texture* texture) {
    point.setTexture(texture);
}
void Point::setSize(Vector2f size) {
    this->size = size;
}
void Point::setRotation(float angle) {

    point.setRotation(angle);

}

/*
void Point::setRotation(Transformable& point, float angle) {
    point.rotate(angle);
}
*/