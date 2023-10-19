#include "Engine.hpp"

void Engine::startupView() {
    string startLog = "[INFO] " + getCurrentTime() + " Main menu started ";
    setLogContent(startLog);
    sf::RenderWindow window(sf::VideoMode(400, 400), "Menu");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Blue);
    window.setFramerateLimit(60);
    sf::Text text;
    setSettingsOf(text);
    sf::Clock clock;
    while (window.isOpen()) {
        float currentTime = clock.restart().asSeconds();
        string fpsText = getFramePerSecondText(currentTime);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int elapsed = checkTimer();
        if (elapsed > 5) 
            break;
        setStringOf(text, fpsText);
        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }
}

string Engine::getCurrentTime() {
    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timeStringBuffer[50] = "";
    ctime_s(timeStringBuffer, 27, &timeNow);
    string timeString = timeStringBuffer;
    timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.cend());
    return timeString;
}

string Engine::getFramePerSecondText(float currentTime) {
    float fps = round(1.0f / currentTime);
    string fpsText = to_string(fps);
    int decimalPlacePos = fpsText.find(".000000");
    fpsText.erase(decimalPlacePos);
    return fpsText;
}

int Engine::checkTimer() {
    sf::Time elapsed1 = clock.getElapsedTime();
    return elapsed1.asSeconds();
}

void Engine::setSettingsOf(sf::Text &text) {
    sf::Font font = loadArialFont();
    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
}

void Engine::setStringOf(sf::Text& text, string fpsText) {
    text.setString("FPS: " + fpsText);
}

sf::Font Engine::loadArialFont() {
    sf::Font font;
    string logContent = "";
    if (!font.loadFromFile("arial.ttf")) 
        setLogContent("[ERROR] " + getCurrentTime() + " Unsuccessfull arial font load");
    else 
        setLogContent("[INFO] " + getCurrentTime() + " Arial font was successfully loaded");
    return font;
}

void Engine::openSettings() {
    sf::RenderWindow window(sf::VideoMode(200, 400), "Opcje uruchamiania");
    sf::RectangleShape resolution1;
    sf::RectangleShape resolution2;
    sf::RectangleShape resolution3;
    sf::Text chosenResolution;
    sf::Font font = loadArialFont();
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    resolution1.setSize(sf::Vector2f(160, 50));//dodac tu res 1280x720
    resolution1.setFillColor(sf::Color(25, 55, 60, 255));
    resolution1.setPosition(sf::Vector2f(20, 100));
    text1.setFont(font);
    text1.setString("1280 x 720");
    text1.setCharacterSize(28);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(20, 100));
    resolution2.setSize(sf::Vector2f(160, 50));//dodac tu res 1366x768
    resolution2.setFillColor(sf::Color::Green);
    resolution2.setPosition(sf::Vector2f(20, 180));
    text2.setFont(font);
    text2.setString("1366 x 768");
    text2.setCharacterSize(28);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(20, 180));
    resolution3.setSize(sf::Vector2f(160, 50));//dodac tu res 1600x900
    resolution3.setFillColor(sf::Color::Green);
    resolution3.setPosition(sf::Vector2f(20, 260));
    text3.setFont(font);
    text3.setString("1600 x 900");
    text3.setCharacterSize(28);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sf::Vector2f(20, 260));
    //Dodać tytuł gry
    //Dodać przycisk graj + wywołanie engine.startupView na evencie onClick
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                startupView();
            }
        }
        window.clear();
        window.draw(resolution1);
        window.draw(resolution2);
        window.draw(resolution3);
        window.display();
    }
}

void Engine::setLogContent(string logContent) {
    this->logContent = logContent;
    this->logFilePath = "logs.log";
    if (!validateLogContentFormat()) {
        string error = "[ERROR] " + getCurrentTime() + " Uncorrect log format";
        this->logContent = error;
    }
    saveLog();
}

void Engine::saveLog() {
    fstream fileStream;
    fileStream.open(logFilePath, ios::app);
    fileStream << logContent << endl;
    fileStream.close();
}

bool Engine::validateLogContentFormat() {
    int isValidErrorStart = this->logContent.find("[ERROR]");
    int isValidInfoStart = this->logContent.find("[INFO]");
    int isValidDebugStart = this->logContent.find("[DEBUG]");
    if (isValidErrorStart != string::npos || isValidInfoStart != string::npos || isValidDebugStart != string::npos) {
        cout << this->logContent << endl;
        return true;
    }
    else
        return false;
}

/*
    Tutaj dodawać przyszłe metody obsługi myszki/klawiatury
*/

int main() {
    Engine engine;
    engine.openSettings();
    return 0;
}