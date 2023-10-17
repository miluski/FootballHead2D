#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Settings {
public:
    void openSettings() {
        sf::RenderWindow window(sf::VideoMode(200, 400), "Uruchom gre!");
        sf::RectangleShape resolution1;
        sf::RectangleShape resolution2;
        sf::RectangleShape resolution3;
        sf::Text chosenResolution;
        sf::Font font;
        sf::Text text1;

        //Dodać tytuł gry

        //font.loadFromFile("arial.ttf");
        //text1.setFont(font);
        //text1.setString("Hello world");
        //text1.setCharacterSize(24);
        //text1.setFillColor(sf::Color::Red);
        //text1.setStyle(sf::Text::Bold | sf::Text::Underlined);

        resolution1.setSize(sf::Vector2f(160,50));//dodac tu res 1280x720
        resolution1.setFillColor(sf::Color::Green);
        resolution1.setPosition(sf::Vector2f(20, 100));

        resolution2.setSize(sf::Vector2f(160, 50));//dodac tu res 1366x768
        resolution2.setFillColor(sf::Color::Green);
        resolution2.setPosition(sf::Vector2f(20, 180));
        
        resolution3.setSize(sf::Vector2f(160, 50));//dodac tu res 1600x900
        resolution3.setFillColor(sf::Color::Green);
        resolution3.setPosition(sf::Vector2f(20, 260));

        //Dodać przycisk graj 

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(resolution1);
            window.draw(resolution2);
            window.draw(resolution3);
            window.display();
        }

    }
        
};


class Engine {
public:
    void initialize() {
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }
    }
};

int main()
{
    //Engine engine;
    //engine.initialize();

    Settings settings;
    settings.openSettings();

    return 0;
}