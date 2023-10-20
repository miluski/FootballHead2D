#include "Engine.hpp"

int globalEngineX = 400;
int globalEngineY = 400;

void Engine::startupView() {
    sf::RenderWindow window(sf::VideoMode(globalEngineX, globalEngineY), "SFML works!");
    sf::CircleShape shape(200.f);
    sf::Clock clock;
    shape.setFillColor(sf::Color::Blue);
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


void Settings::openSettings() {
    sf::RenderWindow window(sf::VideoMode(200, 440), "Uruchom gre!");
    sf::RectangleShape resolution1;
    sf::RectangleShape resolution2;
    sf::RectangleShape resolution3;
    sf::RectangleShape grajButton;
    sf::Text chosenResolution;
    sf::Font font;
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::IntRect r1(20, 100, 160, 50);
    sf::IntRect r2(20, 180, 160, 50);
    sf::IntRect r3(20, 260, 160, 50);
    sf::IntRect r4(20, 340, 160, 50);
    int mx = 0;
    int my = 0;

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Font load Failed!" << std::endl;
    }

    resolution1.setSize(sf::Vector2f(160, 50));//dodac tu res 1280x720
    resolution1.setFillColor(sf::Color::Green);
    resolution1.setPosition(sf::Vector2f(20, 100));
    text1.setFont(font);
    text1.setString("1280 x 720");
    text1.setCharacterSize(28);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(27, 105));

    resolution2.setSize(sf::Vector2f(160, 50));//dodac tu res 1366x768
    resolution2.setFillColor(sf::Color::Green);
    resolution2.setPosition(sf::Vector2f(20, 180));
    text2.setFont(font);
    text2.setString("1366 x 768");
    text2.setCharacterSize(28);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(27, 185));

    resolution3.setSize(sf::Vector2f(160, 50));//dodac tu res 1600x900
    resolution3.setFillColor(sf::Color::Green);
    resolution3.setPosition(sf::Vector2f(20, 260));
    text3.setFont(font);
    text3.setString("1600 x 900");
    text3.setCharacterSize(28);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sf::Vector2f(27, 265));

    grajButton.setSize(sf::Vector2f(160, 50));//dodac tu res 1600x900
    grajButton.setFillColor(sf::Color::Red);
    grajButton.setPosition(sf::Vector2f(20, 340));
    text4.setFont(font);
    text4.setString("Graj!");
    text4.setCharacterSize(28);
    text4.setFillColor(sf::Color::White);
    text4.setPosition(sf::Vector2f(70, 345));

    //setResolutionSettings(resolution1, 20, 100); //dodac tu res 1280x720
    //setResolutionSettings(resolution2, 20, 180); // 2 rozdzialka
    //setResolutionSettings(resolution3, 20, 260); // 3 rozdzialka

    //Dodać przycisk graj + wywołanie engine.startupView na evencie onClick
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                engine.startupView();
            }
            

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                    bool b1 = r1.contains(mx, my);
                    bool b2 = r2.contains(mx, my);
                    bool b3 = r3.contains(mx, my);
                    bool b4 = r4.contains(mx, my);
                    if (b1 == true){
                        resolution1.setFillColor(sf::Color::Red);
                        resolution2.setFillColor(sf::Color::Green);
                        resolution3.setFillColor(sf::Color::Green);
                    }
                    if (b2 == true){
                        resolution1.setFillColor(sf::Color::Green);
                        resolution2.setFillColor(sf::Color::Red);
                        resolution3.setFillColor(sf::Color::Green);
                    }
                    if (b3 == true){
                        resolution1.setFillColor(sf::Color::Green);
                        resolution2.setFillColor(sf::Color::Green);
                        resolution3.setFillColor(sf::Color::Red);
                    }

                    if (b4 == true) {
                        if (resolution1.getFillColor() == sf::Color::Red) {
                            //uruchom silnikowi rozdzielczosc 1
                            cout << "rozdzielczosc 1";
                            globalEngineX = 1280;
                            globalEngineY = 720;
                        }
                        else if (resolution2.getFillColor() == sf::Color::Red) {
                            //uruchom silnikowi rozdzielczosc 2
                            cout << "rozdzielczosc 2";
                            globalEngineX = 1366;
                            globalEngineY = 768;
                        }
                        else if (resolution3.getFillColor() == sf::Color::Red) {
                            //uruchom silnikowi rozdzielczosc 3
                            cout << "rozdzielczosc 3";
                            globalEngineX = 1600;
                            globalEngineY = 900;
                        }
                        else {
                            //nic nie rob albo wyrzuc blad ze uzytkownik nie kliknal graj
                            cout << "Zle kliknoles";
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(resolution1);
        window.draw(text1);
        window.draw(resolution2);
        window.draw(text2);
        window.draw(resolution3);
        window.draw(text3);
        window.draw(grajButton);
        window.draw(text4);
        window.display();
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