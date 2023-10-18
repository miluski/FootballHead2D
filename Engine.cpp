#include "Engine.hpp"

void Engine::startupView() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Blue);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int elapsed = timer.checkTimer();
        if (elapsed > 5) 
            break;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Load Failed!" << std::endl;
            break;
        }
        sf::Text text;
        text.setFont(font);
        text.setString("HALO");
        text.setCharacterSize(48);
        text.setFillColor(sf::Color::White);
        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }
}

void Settings::openSettings() {
    sf::RenderWindow window(sf::VideoMode(200, 400), "Uruchom gre!");
    sf::RectangleShape resolution1;
    sf::RectangleShape resolution2;
    sf::RectangleShape resolution3;
    sf::Text chosenResolution;
    sf::Font font;
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
    resolution1.setSize(sf::Vector2f(160, 50));//dodac tu res 1280x720
    resolution1.setFillColor(sf::Color::Green);
    resolution1.setPosition(sf::Vector2f(20, 100));
    resolution2.setSize(sf::Vector2f(160, 50));//dodac tu res 1366x768
    resolution2.setFillColor(sf::Color::Green);
    resolution2.setPosition(sf::Vector2f(20, 180));
    resolution3.setSize(sf::Vector2f(160, 50));//dodac tu res 1600x900
    resolution3.setFillColor(sf::Color::Green);
    resolution3.setPosition(sf::Vector2f(20, 260));
    //Dodać przycisk graj + wywołanie engine.startupView na evencie onClick
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                engine.startupView();
            }
        }
        window.clear();
        window.draw(resolution1);
        window.draw(resolution2);
        window.draw(resolution3);
        window.display();
    }
}

int Timer::checkTimer() {
    sf::Time elapsed1 = clock.getElapsedTime();
    return elapsed1.asSeconds();
}

Logs::Logs() {
    this->logFilePath = "logs.log";
}

void Logs::setLogContent(string logContent) {
    this->logContent = logContent;
    if (!validateLogContentFormat())       
        setErrorLogContent();
}

bool Logs::validateLogContentFormat() {
    int isValidErrorStart = this->logContent.find("[ERROR]");
    int isValidInfoStart = this->logContent.find("[INFO]");
    int isValidDebugStart = this->logContent.find("[DEBUG]");
    if (isValidErrorStart != string::npos || isValidInfoStart != string::npos || isValidDebugStart != string::npos) {
        cout << this->logContent;
        return true;
    }
    else
        return false;
}

void Logs::setErrorLogContent() {
    time_t now = time(0);
    char dateTime[50];
    ctime_s(dateTime, 50, &now);
    string convertedDateTime = dateTime;
    string oldLogContent = this->logContent;
    string error = "[ERROR] " + convertedDateTime + " Uncorrect log format, log content: " + oldLogContent;
    this->logContent = error;
    cout << error << endl;
}

void Logs::saveLog() {
    fstream fileStream;
    fileStream.open(logFilePath, ios::app);
    fileStream << logContent << endl;
    fileStream.close();
}

int main() {
    Settings settings;
    settings.openSettings();
    Logs logs;
    logs.setLogContent("[INFO] testowyLog");
    logs.saveLog();
    return 0;
}