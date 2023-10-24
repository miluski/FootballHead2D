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
enum rectNames {RESOLUTION_1=1, RESOLUTION_2=2, RESOLUTION_3=3, PLAY=4};

class Engine {
public:
    sf::Vector2u windowSize;
    int activeWindowName;
    static Engine& getInstance() {
        static Engine engine;
        return engine;
    }
    void mainWindowSetup();
    void clearWindowToColor(sf::RenderWindow& window, sf::Color color);
    void clearSpriteToColor(sf::Sprite& sprite, sf::Color color);
    void setSecondBufferTexture(sf::Texture);
private:
    string activeBuffer = "main";
    sf::RectangleShape* resolution1Button = getButton(20, sf::Color::Green);
    sf::RectangleShape* resolution2Button = getButton(100, sf::Color::Green);
    sf::RectangleShape* resolution3Button = getButton(180, sf::Color::Green);
    sf::RenderTexture* mainBuffer;
    sf::RenderTexture* secondBuffer;
    sf::Clock clock;
    sf::Font font;
    string logContent;
    sf::Clock breakClock;
    sf::Text* getText();
    sf::Font* getArialFont();
    void serveWindowCloseEvent(sf::RenderWindow&);
    void settingsWindowSetup(sf::RenderWindow*);
    void drawButtonsAt(sf::RenderWindow*);
    void handleBuffers(sf::RenderWindow*);
    sf::RectangleShape* getButton(float, sf::Color);
    int getRectNameWhenMouseIsPressedIn(sf::RenderWindow*);
    string getFramePerSecondText(float);
    void setWidthAndHeight(sf::RectangleShape*, sf::RectangleShape*, sf::RectangleShape*);
    void drawTextsAt(sf::RenderWindow*);
    sf::Text* getText(string content);
    void menuWindowSetup(sf::RenderWindow*, sf::Text, string);
    void setLogContent(string);
    bool validateLogContentFormat();
    string getCurrentTime();
    void saveLog();
};