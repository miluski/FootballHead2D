#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

class Timer {
public:
    sf::Clock clock;
    int checkTimer() {
        sf::Time elapsed1 = clock.getElapsedTime();
        return elapsed1.asSeconds();
    }
};

class Engine {
public:
    Timer timer;
    void initialize() {
        sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
        sf::CircleShape shape(200.f);
        shape.setFillColor(sf::Color::Blue);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            //sf::Time elapsed = clock.restart();
            //updateGame(elapsed);

            int elapsed = timer.checkTimer();

            if (elapsed > 5) {
                break;
            }

            sf::Font font;
            if (!font.loadFromFile("arial.ttf"))
            {
                std::cout << "Load Failed!" << std::endl;
                break;
            }

            sf::Text text;

            // select the font
            text.setFont(font); // font is a sf::Font

            // set the string to display
            text.setString("HALO");

            // set the character size
            text.setCharacterSize(48); // in pixels, not points!

            // set the color
            text.setFillColor(sf::Color::White);


            window.clear();
            window.draw(shape);
            window.draw(text);
            window.display();
        }
    }
};

int main()
{
    Engine engine;
    engine.initialize();

    return 0;
}