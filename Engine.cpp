#include "Engine.hpp"

int globalEngineX = 400;
int globalEngineY = 400;

void Engine::startupView() {
    sf::RenderWindow window(sf::VideoMode(globalEngineX, globalEngineY), "SFML works!");
    sf::CircleShape shape(200.f);
    sf::Clock clock;
    shape.setFillColor(sf::Color::Blue);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        float currentTime = clock.restart().asSeconds();
        float fps = 1.0f / currentTime;
        cout << fps << endl;
        sf::Event event;
        while (window.pollEvent(event)) {
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
    }
}

void Settings::setResolutionSettings(sf::RectangleShape resolution, float X, float Y) {
    resolution.setSize(sf::Vector2f(160, 50));
    resolution.setFillColor(sf::Color::Green);
    resolution.setPosition(sf::Vector2f(X, Y));
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