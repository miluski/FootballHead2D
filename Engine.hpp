#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

class Engine {
public:
    void initialize();
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