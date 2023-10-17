#include "Engine.hpp"

void Engine::initialize() {
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
    Engine engine;
    engine.initialize();
    Logs logs;
    logs.setLogContent("[INFO] testowyLog");
    logs.saveLog();
    return 0;
}