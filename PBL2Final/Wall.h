#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Wall {
private:
	RectangleShape wallShape;
	Texture tx_wall;
public:
	Wall();
	Wall(Vector2f pos, Vector2f size);
	RectangleShape getShape();
	void setTexture(sf::Texture* texture);
};
