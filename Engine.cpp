#include "Engine.hpp"

void Engine::mainWindowSetup() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock breakClock;
    font = *getArialFont();
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        serveWindowCloseEvent(window);
        float elapsed = breakClock.getElapsedTime().asSeconds();
        if (elapsed > 5)
            break;
        switch (activeWindowName) {
            case STARTUP_SETTINGS:
                settingsWindowSetup(&window);
            break;
            case MENU:
                menuWindowSetup(&window);
            break;
            case GAME:
            break;
            case GAME_HELPER:
            break;
        }
        window.display();
    }
}

void Engine::serveWindowCloseEvent(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Engine::settingsWindowSetup(sf::RenderWindow* window) {
    window->setTitle("Ustawienia gry");
    sf::RectangleShape* resolution1Button = getResolutionButton(window->getSize(), 20);
    sf::RectangleShape* resolution2Button = getResolutionButton(window->getSize(), 80);
    sf::RectangleShape* resolution3Button = getResolutionButton(window->getSize(), 140);
    sf::Text* chooseRes = getText("Wybierz rozdzielczość aby rozpocząć");
    sf::Text* resolution1 = getText("1280 x 720");
    sf::Text* resolution2 = getText("1366 x 768");
    sf::Text* resolution3 = getText("1600 x 900");
    chooseRes->setPosition(140, 110);
    resolution1->setPosition(140, 130);
    resolution2->setPosition(140, 190);
    resolution3->setPosition(140, 250);
    window->clear();
    window->draw(*resolution1Button);
    window->draw(*resolution2Button);
    window->draw(*resolution3Button);
    window->draw(*chooseRes);
    window->draw(*resolution1);
    window->draw(*resolution2);
    window->draw(*resolution3);
}

sf::RectangleShape* Engine::getResolutionButton(sf::Vector2u windowSize, float yShift) {
    sf::Vector2f centerPoint(windowSize.x / 2, windowSize.y / 2);
    sf::RectangleShape* resolutionButton = new sf::RectangleShape();
    sf::FloatRect rectBounds = resolutionButton->getLocalBounds();
    resolutionButton->setSize(sf::Vector2f(200, 50));
    resolutionButton->setFillColor(sf::Color::Green);
    resolutionButton->setPosition(110, (((windowSize.y)/2 - rectBounds.height) / 2)+yShift);
    return resolutionButton;
}

void Engine::menuWindowSetup(sf::RenderWindow* window) {
    setLogContent("[INFO] " + getCurrentTime() + " Main menu started ");
    sf::Clock fpsClock;
    sf::Text* fpsTextPlace = getText();
    float currentTime = fpsClock.restart().asSeconds();
    string fpsText = getFramePerSecondText(currentTime);
    fpsTextPlace->setString(fpsText);
    window->setTitle("Menu");
    window->setSize(windowSize);
    window->clear();
    window->draw(*fpsTextPlace);
}

void Engine::clearWindowToColor(sf::RenderWindow& window, sf::Color color) {
    window.clear(color);
}

void Engine::clearSpriteToColor(sf::Sprite& sprite, sf::Color color) {
    sprite.setColor(color);
}

sf::Text* Engine::getText() {
    sf::Text* text = new sf::Text();
    text->setFont(font);
    text->setFillColor(sf::Color::White);
    text->setCharacterSize(25);
    return text;
}

sf::Text* Engine::getText(string content) {
    sf::Text* text = new sf::Text();
    text->setFont(font);
    text->setFillColor(sf::Color::White);
    text->setString(content);
    text->setCharacterSize(28);
    return text;
}

string Engine::getCurrentTime() {
    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timeStringBuffer[50] = "";
    ctime_s(timeStringBuffer, 50, &timeNow);
    string timeString = timeStringBuffer;
    timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.cend());
    return timeString;
}

string Engine::getFramePerSecondText(float currentTime) {
    float fps = 1.0f / currentTime;
    string fpsText = to_string(round(fps));
    size_t decimalPlacePos = fpsText.find(".000000");
    fpsText.erase(decimalPlacePos);
    return "FPS: " + fpsText;
}

sf::Font* Engine::getArialFont() {
    sf::Font* font = new sf::Font();
    string logContent = "";
    if (!font->loadFromFile("arial.ttf")) 
        setLogContent("[ERROR] " + getCurrentTime() + " Unsuccessfull arial font load");
    else 
        setLogContent("[INFO] " + getCurrentTime() + " Arial font was successfully loaded");
    return font;
}

void Engine::setLogContent(string logContent) {
    this->logContent = logContent;
    if (!validateLogContentFormat()) {
        string error = "[ERROR] " + getCurrentTime() + " Uncorrect log format";
        this->logContent = error;
    }
    saveLog();
}

void Engine::saveLog() {
    fstream fileStream;
    fileStream.open("logs.log", ios::app);
    fileStream << logContent << endl;
    fileStream.close();
    cout << logContent << endl;
}

bool Engine::validateLogContentFormat() {
    size_t isValidErrorStart = this->logContent.find("[ERROR]");
    size_t isValidInfoStart = this->logContent.find("[INFO]");
    size_t isValidDebugStart = this->logContent.find("[DEBUG]");
    if (isValidErrorStart != string::npos || isValidInfoStart != string::npos || isValidDebugStart != string::npos) 
        return true;
    else
        return false;
}

/*
    Tutaj dodawać przyszłe metody obsługi myszki/klawiatury
*/

int main() {
    Engine::getInstance().activeWindowName = STARTUP_SETTINGS;
    Engine::getInstance().mainWindowSetup();
    return 0;
}