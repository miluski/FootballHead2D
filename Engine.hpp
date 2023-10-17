#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
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
    void initialize();
    Timer timer;
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