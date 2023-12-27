#include"Setting.h"



Setting::Setting(RenderWindow& game, int& pagenum) :game(game), pagenum(pagenum) {
	//speed = " ";
	inputSpeed = 1;
	font.loadFromFile("../Data/Game Shark.otf");
	setupText(&enterSpeedText, font, "Enter your speed: ", 30, Color::Black);
	setupText(&speedText, font, speed, 30, Color::Cyan);
	enterSpeedText.setPosition(100, 100);
	speedText.setPosition(200, 100);

	//font.loadFromFile("../Data/Game Shark.otf");
	setupText(&enterNameText, font, "Enter your name: ", 30, Color::Black);
	setupText(&nameText, font, name, 30, Color::Cyan);
	nameText.setPosition(200, 100);
	enterNameText.setPosition(100, 100);

	alertFont.loadFromFile("../Data/HelloMonday.otf");

	tx2.loadFromFile("../Data/back.png");
	sprite2.setColor(Color::White);
	sprite2.setTexture(tx2);
	sprite2.setPosition(30, 500);
	sprite2.setScale(0.15f, 0.15f);

	tx3.loadFromFile("../Data/next.png");
	sprite3.setColor(Color::White);
	sprite3.setTexture(tx3);
	sprite3.setPosition(700, 500);
	sprite3.setScale(0.15f, 0.15f);


	backgroundMenu.loadFromFile("../Data/bg.png");
	bg.setTexture(backgroundMenu);

}

void Setting::Speed() {

	while (game.isOpen()) {
		Event event;
		while (game.pollEvent(event)) {
			if (event.type == Event::Closed) {
				game.close();
			}
			if (event.type == Event::KeyPressed && event.key.code != Keyboard::Enter) {
				try {
					if (event.key.code == Keyboard::Backspace && speed.size() > 0) {
						speed.resize(speed.size() - 1);
					}


					else if ((event.key.code >= Keyboard::Num0 && event.key.code <= Keyboard::Num9)) {
						char digit = '0' + (event.key.code - Keyboard::Num0);
						speed += digit;
						inputSpeed = stoi(speed);


					}

					else {
						throw invalid_argument("");
					}
				}
				catch (const invalid_argument& e) {
					Alert();
				}

				enterSpeedText.setString("Enter your speed: " + speed);



			}


			//}	

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				//inputSpeed = stoi(speed);


				try {
					//cout << inputSpeed;
					if (inputSpeed <= 0 || inputSpeed > 10) {
						throw invalid_argument("");
					}
					else {
						Name();
						return;
					}
				}
				catch (const invalid_argument& e) {
					Alert();
				}

				//pagenum = 100;


			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Button::Left) {
					Vector2i mousePosition = Mouse::getPosition(game);
					//inputSpeed = stoi(speed);



					try {
						//inputSpeed = stoi(speed);
						//cout << inputSpeed;
						if (sprite3.getGlobalBounds().contains(Vector2f(mousePosition))) {
							if (inputSpeed <= 0 || inputSpeed > 10) {
								throw invalid_argument("");
							}
							else {
								Name();
								return;
							}
						}
						else if (sprite2.getGlobalBounds().contains(Vector2f(mousePosition))) {
							//cout << ",,,";
							pagenum = 100;

							return;
						}
						else throw invalid_argument("");

					}
					catch (const invalid_argument& e) {
						Alert();
					}

				}

			}


		}
		game.clear();
		game.draw(bg);
		game.draw(sprite2);
		game.draw(sprite3);

		game.draw(enterSpeedText);
		game.display();

	}
}
void Setting::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(colour);

}

int Setting::getInputSpeed() {
	return inputSpeed;
}
void Setting::Name() {

	while (game.isOpen()) {
		Event event;

		while (game.pollEvent(event)) {

			if (event.type == Event::TextEntered) {
				if (event.text.unicode >= 48 && event.text.unicode <= 122) {
					name += static_cast<char>(event.text.unicode);
				}
				enterNameText.setString("Enter your name: " + name);
			}
			if (event.type == Event::KeyPressed) { // xu li backspace
				if (event.key.code == Keyboard::Backspace && name.size() > 0) {
					name.resize(name.size() - 1);
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
				pagenum = 0;
				return;
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Button::Left) {
					Vector2i mousePosition = Mouse::getPosition(game);
					if (sprite2.getGlobalBounds().contains(Vector2f(mousePosition))) {
						//cout << "...";
						//pagenum = 1;
						Speed();
						//return;
					}
					if (sprite3.getGlobalBounds().contains(Vector2f(mousePosition))) {
						//Engine engine;
						pagenum = 0;
						//break;
						//return;
					}
					return;

				}
			}
			//return;



		}
		game.clear();
		game.draw(bg);
		game.draw(enterNameText);
		game.draw(sprite2);
		game.draw(sprite3);
		game.display();

	}
}
string Setting::getName() {
	return name;
}

void Setting::Alert() {
	RenderWindow alertWindow(VideoMode(600, 100), "", Style::Default);
	setupText(&alertText, alertFont, "Please enter a speed between 1 and 10!!!", 25, Color{ 240, 10, 20 });
	alertText.setPosition(Vector2f(60, 30));
	while (alertWindow.isOpen()) {
		sf::Event event;
		while (alertWindow.pollEvent(event)) {
			if (event.type == Event::Closed) {
				alertWindow.close();
			}
		}
		alertWindow.clear();
		alertWindow.draw(alertText);
		alertWindow.display();
	}
}

bool Setting::isPlayerExist(const vector<Player>& players, const string& playerName) {
	for (const auto& player : players) {
		if (player.getName() == playerName) {
			return true;  // Tên người chơi đã tồn tại
		}
	}
	return false;  // Tên người chơi chưa tồn tại
}