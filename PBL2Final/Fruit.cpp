#include "Fruit.h"


void Fruit::setPos(sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}
RectangleShape Fruit::getSprite() {

    return sprite;
}
//void Fruit::setTexture(Texture* texture) {
  //  sprite.setTexture(texture);
//}

Fruit::Fruit() {
    Vector2f startPos(400, 300);
    sprite.setSize(Vector2f(20, 20));
    // sprite.setFillColor(Color::White);
    sprite.setPosition(startPos);
    tx_apple.loadFromFile("../Data/apple.png");
    sprite.setTexture(&tx_apple);

}
