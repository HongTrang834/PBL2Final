#include "Menu.h"
#include<iostream>

Menu::Menu(float width, float height) {


	game.create(VideoMode(800, 600), "Menu");
	mainFont.loadFromFile("../Data/Game Shark.otf");

	setupText(&mainMenuText[0], mainFont, "Play", 38, Color{ 255,204,0 });
	mainMenuTextBounds[0] = mainMenuText[0].getLocalBounds();
	mainMenuTextBounds[0].width += 10;
	mainMenuTextBounds[0].height += 10;
	mainMenuTextBounds[0].top = 150;
	mainMenuTextBounds[0].left = width / 2 - mainMenuTextBounds[0].width / 2;
	mainMenuText[0].setPosition(Vector2f(mainMenuTextBounds[0].left, mainMenuTextBounds[0].top));
	mainMenuText[0].setOutlineColor(Color::Black);
	mainMenuText[0].setOutlineThickness(5);

	setupText(&mainMenuText[1], mainFont, "Setting", 30, Color::White);
	mainMenuTextBounds[1] = mainMenuText[1].getLocalBounds();
	mainMenuTextBounds[1].width += 10;
	mainMenuTextBounds[1].height += 10;
	mainMenuTextBounds[1].top = 250;
	mainMenuTextBounds[1].left = width / 2 - mainMenuTextBounds[1].width / 2;
	mainMenuText[1].setPosition(Vector2f(mainMenuTextBounds[1].left, mainMenuTextBounds[1].top));
	mainMenuText[1].setOutlineColor(Color::Black);
	mainMenuText[1].setOutlineThickness(2);

	setupText(&mainMenuText[2], mainFont, "Instruction", 30, Color::White);
	mainMenuTextBounds[2] = mainMenuText[1].getLocalBounds();
	mainMenuTextBounds[2].width += 10;
	mainMenuTextBounds[2].height += 10;
	mainMenuTextBounds[2].top = 350;
	mainMenuTextBounds[2].left = width / 2 - mainMenuTextBounds[2].width / 2;
	mainMenuText[2].setPosition(Vector2f(mainMenuTextBounds[2].left, mainMenuTextBounds[2].top));
	mainMenuText[2].setOutlineColor(Color::Black);
	mainMenuText[2].setOutlineThickness(2);

	setupText(&mainMenuText[3], mainFont, "Exit", 30, Color::White);
	mainMenuTextBounds[3] = mainMenuText[3].getLocalBounds();
	mainMenuTextBounds[3].width += 10;
	mainMenuTextBounds[3].height += 10;
	mainMenuTextBounds[3].top = 450;
	mainMenuTextBounds[3].left = width / 2 - mainMenuTextBounds[3].width / 2;
	mainMenuText[3].setPosition(Vector2f(mainMenuTextBounds[3].left, mainMenuTextBounds[3].top));
	mainMenuText[3].setOutlineColor(Color::Black);
	mainMenuText[3].setOutlineThickness(2);


	//selected = 0;
}

Menu::~Menu() {}
void Menu::DrawMenu() {
	for (int i = 0; i < Max_menu; i++) {
		game.draw(mainMenuText[i]);
	}
}

void Menu::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(colour);

}
/*
int Menu::pressed() {
	return selected;
}
*/

void Menu::runMenu() {
	Texture backgroundMenu;
	backgroundMenu.loadFromFile("../Data/bgbg.png");
	Sprite bg;
	bg.setTexture(backgroundMenu);
	int pagenum = 100;
	Setting setting(game, pagenum);
	//Instruction instruction(game, pagenum);

	while (pagenum == 100) {
		while (game.isOpen()) {
			Event event;
			while (game.pollEvent(event)) {
				if (event.type == Event::Closed) {
					game.close();
					break;
				}

				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Button::Left) {
						Vector2i mousePosition = Mouse::getPosition(game);
						if (mainMenuTextBounds[0].contains(Vector2f(mousePosition))) {
							pagenum = 0;
							//mouseClicked = true;

						}
						if (mainMenuTextBounds[1].contains(Vector2f(mousePosition))) {
							pagenum = 1;
							//mouseClicked = true;
						}
						if (mainMenuTextBounds[2].contains(Vector2f(mousePosition))) {
							pagenum = 2;
							//mouseClicked = true;
						}
						if (mainMenuTextBounds[3].contains(Vector2f(mousePosition))) {
							pagenum = -1;
							break;
						}
					}
				}
				if (event.type == Event::MouseMoved) {
					Vector2i mouseMovePosition = Mouse::getPosition(game);
					bool touch = false;

					// Kiểm tra nếu chuột di chuyển đến vị trí của chữ
					for (int i = 0; i < Max_menu; ++i) {
						if (mainMenuTextBounds[i].contains(Vector2f(mouseMovePosition))) {
							mainMenuText[i].setFillColor(Color{ 255,204,0 });
							mainMenuText[i].setCharacterSize(38);
							mainMenuText[i].setOutlineThickness(5);

							// Ghi nhận rằng chuột đã di chuyển đến vị trí chữ
							touch = true;
						}
						else {
							// Chuột không ở vị trí chữ, trả về trạng thái ban đầu
							mainMenuText[i].setFillColor(Color::White);
							mainMenuText[i].setCharacterSize(30);
							mainMenuText[i].setOutlineThickness(2);
						}
					}

					// Kiểm tra nếu chuột đã rời khỏi vị trí chữ
					if (!touch) {
						// Trả về trạng thái ban đầu của tất cả chữ
						for (int i = 0; i < Max_menu; ++i) {
							mainMenuText[i].setFillColor(Color::White);
							mainMenuText[i].setCharacterSize(30);
							mainMenuText[i].setOutlineThickness(2);
						}
					}
				}
			}
			game.clear();
			if (pagenum != 100) {
				break;
			}
			game.draw(bg);
			DrawMenu();
			game.display();
		}
		if (pagenum == -1) {
			game.close();
		}
		if (pagenum == 1) {

			setting.Speed();
			//setting.Name();


		}
		if (pagenum == 2) {

			Instruction instruction(game, pagenum);
			instruction.Show();

			//setting.Speed();
			//setting.Name();


		}
		if (pagenum == 0) {
			//game.clear();
			Engine engine(game, pagenum, setting);
			engine.Play();
		}
	}
}


