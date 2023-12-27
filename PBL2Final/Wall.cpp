#include "Wall.h"
Wall::Wall() {}
void Wall::setTexture(sf::Texture* texture) {
	wallShape.setTexture(texture);
}
Wall::Wall(Vector2f pos, Vector2f size) {
	wallShape.setSize(size);
	//wallShape.setFillColor(Color::White);
	wallShape.setPosition(pos);
}

RectangleShape Wall::getShape() {
	return wallShape;
}

