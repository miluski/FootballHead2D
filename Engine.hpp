#pragma once
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

enum windowNames {STARTUP_SETTINGS=0, MENU=1, GAME=2, GAME_HELPER=3};

class Engine {
public:
    int activeWindowName;
    static Engine& getInstance() {
        static Engine engine;
        return engine;
    }
    void mainWindowSetup();
    void clearWindowToColor(sf::RenderWindow& window, sf::Color color);
    void clearSpriteToColor(sf::Sprite& sprite, sf::Color color);
private:
    sf::Clock clock;
    sf::Font font;
    sf::Vector2u windowSize;
    string logContent;
    void settingsWindowSetup(sf::RenderWindow*);
    void menuWindowSetup(sf::RenderWindow*);
    string getCurrentTime();
    string getFramePerSecondText(float);
    sf::Font* getArialFont();
    sf::Text* getText();
    sf::Text* getText(string content);
    sf::RectangleShape* getResolutionButton(sf::Vector2u windowSize, float);
    bool validateLogContentFormat();
    void setLogContent(string);
    void saveLog();
    void serveWindowCloseEvent(sf::RenderWindow&);
};