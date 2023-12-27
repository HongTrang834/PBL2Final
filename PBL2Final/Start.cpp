#include "Start.h"
#include "Menu.h"

class LoadingBar : public sf::Drawable {
public:
    float width, height;
    sf::RectangleShape outline;
    sf::RectangleShape bar;

    float totalWidth;
    float barWidth;

    LoadingBar() : width(200), height(20), totalWidth(200), barWidth(20) {
        // Set up the outline
        outline.setOutlineThickness(2.0f);

        // Set up the bar
        bar.setFillColor(sf::Color::Green);
    }

    void setSize(float w, float h) {
        width = w;
        height = h;
        totalWidth = width;

        // Set up the outline
        outline.setSize(sf::Vector2f(width, height));
        outline.setPosition(200, 200);

        // Set up the bar
        bar.setSize(sf::Vector2f(barWidth, height - 4)); // Subtracting 4 for the outline
        bar.setPosition(outline.getPosition() + sf::Vector2f(2.0f, 2.0f)); // Inside the outline
    }

    void setOutlineColor(const sf::Color& color) {
        outline.setOutlineColor(color);
    }

    void setPosition(float x, float y) {
        outline.setPosition(x, y);
        bar.setPosition(outline.getPosition() + sf::Vector2f(2.0f, 2.0f)); // Inside the outline
    }

    void update(float progress) {
        if (progress >= 0.0f && progress <= 100.0f) {
            barWidth = (progress / 100.0f) * totalWidth;
            bar.setSize(sf::Vector2f(barWidth, height - 4.0f));
        }
    }
    bool isComplete() {
        return barWidth >= totalWidth;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(outline, states);
        target.draw(bar, states);
    }
};

void Start::starttheGame() {

    window.create(sf::VideoMode(800, 600), "Snake Game");

    window.setFramerateLimit(60);


    Texture backgroundMain;
    backgroundMain.loadFromFile("../Data/SNAKE GAME.png");


    Sprite bgMain(backgroundMain);
    // game.draw(bgMain);

   //  LoadingBar B;
    // B.setPosition(200, 200); // Set the position of the loading bar
     //B.setSize(200, 20);   // Set the size of the loading bar
     //B.setOutlineColor(sf::Color::Black); // Set outline color

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float elapsedTime = clock.getElapsedTime().asSeconds();
        float progress = (elapsedTime / 5.0f) * 100.0f; // Completes in 5 seconds
        // B.update(progress);

        // game.clear();
        window.draw(bgMain);
        //window.draw(B);
        window.display();


        //if (B.isComplete()) {

           //  break;


        // }





        sleep(seconds(1));

        window.close();


    }

    Menu menu(800, 600);
    menu.runMenu();

    //sleep(seconds(2));

}
/*
class loadingBar {
public:
    float width = 200, height = 20;
    RectangleShape outline;
    RectangleShape bar;

    float totalWidth = width;
    float barWidth = 0.0f;
loadingBar(){




    // Set up the outline
    outline.setSize(sf::Vector2f(width, height));
    outline.setOutlineThickness(2.0f);
    outline.setOutlineColor(sf::Color::Black);
    outline.setPosition(50.0f, 50.0f);

    // Set up the bar
    bar.setSize(sf::Vector2f(barWidth, height - 4.0f)); // Subtracting 4 for the outline
    bar.setFillColor(sf::Color::Green);
    bar.setPosition(52.0f, 52.0f); // Inside the outline
 }

void update(float progress) {
    if (progress >= 0.0f && progress <= 100.0f) {
        barWidth = (progress / 100.0f) * totalWidth;
        bar.setSize(sf::Vector2f(barWidth, height - 4.0f));
    }
}
};
*/
