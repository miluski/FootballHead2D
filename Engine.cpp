#include "Engine.hpp"

void Engine::mainWindowSetup() {
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "", sf::Style::Titlebar | sf::Style::Close);
    sf::Text* fpsTextPlace = getText();
    sf::Clock fpsClock;
    font = *getArialFont();
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        float elapsed = breakClock.getElapsedTime().asSeconds();
        if (elapsed > 5)
            window.close();
        serveWindowCloseEvent(window);
        float currentTime = fpsClock.restart().asSeconds();
        string fpsText = getFramePerSecondText(currentTime);
        switch (activeWindowName) {
            case STARTUP_SETTINGS:
                settingsWindowSetup(&window);
            break;
            case MENU:
                menuWindowSetup(&window, *fpsTextPlace, fpsText);
            break;
            case GAME:
                handleBuffers(&window);
            break;
            case GAME_HELPER:
            break;
        }
        window.display();
    }
}

void Engine::setSecondBufferTexture(sf::Texture bufferTexture) {
    secondBuffer->clear();
    secondBuffer->draw(sf::Sprite(bufferTexture));
    secondBuffer->display();
}

void Engine::handleBuffers(sf::RenderWindow* window) {
    if (activeBuffer == "main") {
        mainBuffer->clear();
        mainBuffer->draw(sf::Sprite(secondBuffer->getTexture()));
        mainBuffer->display();
        window->draw(sf::Sprite(mainBuffer->getTexture()));
        activeBuffer = "second";
    }
    else {
        secondBuffer->clear();
        secondBuffer->draw(sf::Sprite(mainBuffer->getTexture()));
        secondBuffer->display();
        window->draw(sf::Sprite(secondBuffer->getTexture()));
        activeBuffer = "main";
    }
}

sf::Text* Engine::getText() {
    sf::Text* text = new sf::Text();
    text->setFont(font);
    text->setFillColor(sf::Color::White);
    text->setCharacterSize(15);
    return text;
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

void Engine::serveWindowCloseEvent(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseMoved)
            breakClock.restart();
    }
}

string Engine::getFramePerSecondText(float currentTime) {
    float fps = 1.0f / currentTime;
    string fpsText = to_string(round(fps));
    size_t decimalPlacePos = fpsText.find(".000000");
    fpsText.erase(decimalPlacePos);
    return "FPS: " + fpsText;
}

void Engine::settingsWindowSetup(sf::RenderWindow* window) {
    window->setTitle("Ustawienia gry");
    window->clear();
    drawButtonsAt(window);
    drawTextsAt(window);
}

void Engine::drawButtonsAt(sf::RenderWindow* window) {
    sf::RectangleShape* playButton = getButton(260, sf::Color::Red);
    int rectName = getRectNameWhenMouseIsPressedIn(window);
    switch (rectName) {
        case RESOLUTION_1:
            resolution1Button = getButton(20, sf::Color::Red);
            resolution2Button = getButton(100, sf::Color::Green);
            resolution3Button = getButton(180, sf::Color::Green);
        break;
        case RESOLUTION_2:
            resolution1Button = getButton(20, sf::Color::Green);
            resolution2Button = getButton(100, sf::Color::Red);
            resolution3Button = getButton(180, sf::Color::Green);
        break;
        case RESOLUTION_3:
            resolution1Button = getButton(20, sf::Color::Green);
            resolution2Button = getButton(100, sf::Color::Green);
            resolution3Button = getButton(180, sf::Color::Red);
        break;
        case PLAY:
            setWidthAndHeight(resolution1Button, resolution2Button, resolution3Button);
        break;
    }
    window->draw(*resolution1Button);
    window->draw(*resolution2Button);
    window->draw(*resolution3Button);
    window->draw(*playButton);
}

sf::RectangleShape* Engine::getButton(float yShift, sf::Color color) {
    sf::RectangleShape* button = new sf::RectangleShape();
    button->setSize(sf::Vector2f(200, 50));
    button->setFillColor(color);
    button->setPosition(100, 40 + yShift);
    return button;
}

int Engine::getRectNameWhenMouseIsPressedIn(sf::RenderWindow* window) {
    sf::IntRect rect1(100, 60, 200, 50);
    sf::IntRect rect2(100, 140, 200, 50);
    sf::IntRect rect3(100, 220, 200, 50);
    sf::IntRect rect4(100, 300, 200, 50);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mouseBounds = sf::Mouse::getPosition(*window);
        int mouseX = mouseBounds.x;
        int mouseY = mouseBounds.y;
        if (rect1.contains(mouseX, mouseY))
            return RESOLUTION_1;
        else if (rect2.contains(mouseX, mouseY))
            return RESOLUTION_2;
        else if (rect3.contains(mouseX, mouseY))
            return RESOLUTION_3;
        else if (rect4.contains(mouseX, mouseY))
            return PLAY;
    }
    return -1;
}

void Engine::setWidthAndHeight(sf::RectangleShape* resolution1Button, sf::RectangleShape* resolution2Button,
    sf::RectangleShape* resolution3Button) {
    if (resolution1Button->getFillColor() == sf::Color::Red) {
        windowSize.x = 1280;
        windowSize.y = 720;
        Engine::getInstance().activeWindowName = MENU;
    }
    else if (resolution2Button->getFillColor() == sf::Color::Red) {
        windowSize.x = 1366;
        windowSize.y = 768;
        Engine::getInstance().activeWindowName = MENU;
    }
    else if (resolution3Button->getFillColor() == sf::Color::Red) {
        windowSize.x = 1600;
        windowSize.y = 900;
        Engine::getInstance().activeWindowName = MENU;
    }
}

void Engine::drawTextsAt(sf::RenderWindow* window) {
    sf::Text* resolution1 = getText("1280 x 720");
    sf::Text* resolution2 = getText("1366 x 768");
    sf::Text* resolution3 = getText("1600 x 900");
    sf::Text* startGame = getText("Uruchom gre");
    resolution1->setPosition(130, 70);
    resolution2->setPosition(130, 150);
    resolution3->setPosition(130, 230);
    startGame->setPosition(120, 310);
    window->draw(*resolution1);
    window->draw(*resolution2);
    window->draw(*resolution3);
    window->draw(*startGame);
}

sf::Text* Engine::getText(string content) {
    sf::Text* text = new sf::Text();
    text->setFont(font);
    text->setFillColor(sf::Color::White);
    text->setString(content);
    text->setCharacterSize(28);
    return text;
}

void Engine::menuWindowSetup(sf::RenderWindow* window, sf::Text fpsTextPlace, string fpsText) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    fpsTextPlace.setString(fpsText);
    window->setTitle("Menu");
    window->setSize(windowSize);
    window->setPosition(sf::Vector2i((desktop.width - windowSize.x) / 2, (desktop.height - windowSize.y) / 2));
    window->clear();
    window->draw(fpsTextPlace);
}

void Engine::clearWindowToColor(sf::RenderWindow& window, sf::Color color) {
    window.clear(color);
}

void Engine::clearSpriteToColor(sf::Sprite& sprite, sf::Color color) {
    sprite.setColor(color);
}

void Engine::setLogContent(string logContent) {
    this->logContent = logContent;
    if (!validateLogContentFormat()) {
        string error = "[ERROR] " + getCurrentTime() + " Uncorrect log format";
        this->logContent = error;
    }
    saveLog();
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

string Engine::getCurrentTime() {
    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timeStringBuffer[50] = "";
    ctime_s(timeStringBuffer, 50, &timeNow);
    string timeString = timeStringBuffer;
    timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.cend());
    return timeString;
}

void Engine::saveLog() {
    fstream fileStream;
    fileStream.open("logs.log", ios::app);
    fileStream << logContent << endl;
    fileStream.close();
    cout << logContent << endl;
}

int main() {
    Engine::getInstance().activeWindowName = STARTUP_SETTINGS;
    Engine::getInstance().windowSize.x = 400;
    Engine::getInstance().windowSize.y = 400;
    Engine::getInstance().mainWindowSetup();
    return 0;
}