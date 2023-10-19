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

class Engine {
public:
    void openSettings();
private:
    sf::Clock clock;
    string logContent;
    string logFilePath;
    void startupView();
    string getCurrentTime();
    string getFramePerSecondText(float);
    int checkTimer();
    void setSettingsOf(sf::Text &);
    void setStringOf(sf::Text&, string);
    sf::Font loadArialFont();
    void installMouse();
    void installKeyboard();
    bool validateLogContentFormat();
    void setLogContent(string);
    void saveLog();
};