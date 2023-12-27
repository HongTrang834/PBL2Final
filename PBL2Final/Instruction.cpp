#include"Instruction.h"



Instruction::Instruction(RenderWindow& game, int& pagenum) :game(game), pagenum(pagenum) {





	ifstream file("../Data/Instruction.txt");

	stringstream buffer;

	buffer << file.rdbuf();

	file.close();
	string textContent = buffer.str();

	font.loadFromFile("../Data/HelloMonday.otf");
	setupText(&instructionText, font, "", 25, Color::Black);
	instructionText.setString(textContent);
	instructionText.setPosition(100, 50);

	tx1.loadFromFile("../Data/arrows.png");
	sprite1.setTexture(tx1);
	sprite1.setPosition(600, 50);
	sprite1.setScale(0.2f, 0.2f);

	tx2.loadFromFile("../Data/back.png");
	sprite2.setColor(Color::White);
	sprite2.setTexture(tx2);
	sprite2.setPosition(30, 500);
	sprite2.setScale(0.15f, 0.15f);


	backgroundMenu.loadFromFile("../Data/bg.png");
	bg.setTexture(backgroundMenu);


}

void Instruction::Show() {
	while (game.isOpen()) {
		Event event;
		while (game.pollEvent(event)) {
			if (event.type == Event::Closed) {
				game.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				pagenum = 100;
				return;
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Button::Left) {
					Vector2i mousePosition = Mouse::getPosition(game);
					if (sprite2.getGlobalBounds().contains(Vector2f(mousePosition))) {
						pagenum = 100;
						return;
					}
				}
			}
		}
		game.clear();
		game.draw(bg);
		game.draw(instructionText);
		game.draw(sprite1);
		game.draw(sprite2);
		game.display();

	}
}
void Instruction::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(colour);

}
