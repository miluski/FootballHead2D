#pragma once
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace std;

class Timer {
public:
    sf::Clock clock;
    int checkTimer();
};

class Engine {
public:
    void startupView();
    Timer timer;
};

class Settings {
public:
    void openSettings();
    Engine engine;
};

class Logs {
public:
    Logs();
    void setLogContent(string);
    void saveLog();
private:
    bool validateLogContentFormat();
    void setErrorLogContent();
    string logContent;
    string logFilePath;
};