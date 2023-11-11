#include "Engine.hpp"

void Engine::mainWindowSetup() {
    font = *getFont("arial");
    setFrameRateLimit();
    Image iconImage;
    iconImage.loadFromFile("elements/Pilka.png");
    window->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());
    window->setVerticalSyncEnabled(true);
    string fps = "";
    while (window->isOpen()) {
        float elapsed = breakClock.getElapsedTime().asSeconds();
        float currentTime = fpsClock.getElapsedTime().asSeconds();
        fps = getFramePerSecondText(currentTime);
        if (elapsed > 300)
            window->close();
        serveWindowCloseEvent();
        switch (activeWindowName) {
            case STARTUP_SETTINGS:
                settingsWindowSetup();
            break;
            case MENU:
                menuWindowSetup();
            break;
            case GAME:
                gameWindowSetup(fps);
            break;
            case GAME_HELPER:
                gameHelperWindowSetup();
            break;
        }
    }
}

void Engine::settingsWindowSetup() {
    window->setTitle("Ustawienia gry");
    getInstance().clearWindowToColor(Color::Black);
    drawButtons();
    drawTexts();
    window->display();
}

void Engine::menuWindowSetup() {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        window->setTitle("Menu");
        window->setSize(*windowSize);
        music.openFromFile("sounds/menu_music.wav");
        music.play();
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        mainBuffer.create(windowSize->x, windowSize->y);
        secondBuffer.create(windowSize->x, windowSize->y);
        centered = true;
    }
    else 
        setMenuBackground();
    if (music.getStatus() != Music::Status::Playing)
        music.play();
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        centered = false;
        activeWindowName = GAME;
    }
}

void Engine::gameWindowSetup(string currentTime) {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        font = *getFont("Pixellari");
        music.stop();
        window->setTitle("FootballHead2D");
        window->setSize(*windowSize);
        setFrameRateLimit();
        backgroundRenderTexture->create(window->getSize().x, window->getSize().y);
        music.openFromFile("sounds/stadium_crowd.wav");
        music.play();
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        centered = true;
    }
    else 
        setGameBackground(currentTime);
    if (music.getStatus() != Music::Status::Playing)
        music.play();
}

void Engine::gameHelperWindowSetup() {
    VideoMode desktop = VideoMode::getDesktopMode();
    setFrameRateLimit();
    if (!centered) {
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        centered = true;
    }
    window->setTitle("Game Helper");
    window->setSize(*windowSize);
}

void Engine::setWidthAndHeight(RectangleShape* resolution1Button, RectangleShape* resolution2Button,
    RectangleShape* resolution3Button) {
    if (resolution1Button->getFillColor() == Color::Red) {
        windowSize->x = 1280;
        windowSize->y = 720;
        getInstance().activeWindowName = MENU;
    }
    else if (resolution2Button->getFillColor() == Color::Red) {
        windowSize->x = 1366;
        windowSize->y = 768;
        getInstance().activeWindowName = MENU;
    }
    else if (resolution3Button->getFillColor() == Color::Red) {
        windowSize->x = 1600;
        windowSize->y = 900;
        getInstance().activeWindowName = MENU;
    }
}

void Engine::setMainBufferTexture(Sprite textureSprite) {
    mainBuffer.clear();
    mainBuffer.draw(textureSprite);
    mainBuffer.display();
}

void Engine::setSecondBufferTexture(Sprite textureSprite) {
    secondBuffer.clear();
    secondBuffer.draw(textureSprite);
    secondBuffer.display();
}

void Engine::setFrameRateLimit() {
    window->setFramerateLimit(60);
}

void Engine::setLogContent(string logContent) {
    this->logContent = logContent;
    if (!validateLogContentFormat()) {
        string error = "[ERROR] " + getCurrentTime() + " Uncorrect log format";
        this->logContent = error;
    }
    saveLog();
}

RenderWindow* Engine::getMainWindow() {
    return window;
}

Text Engine::getText(Color color) {
    Text text;
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(24);
    return text;
}

Text Engine::getText(Color color, string content) {
    Text text;
    text.setFont(font);
    text.setFillColor(color);
    text.setString(content);
    text.setCharacterSize(28);
    return text;
}

RectangleShape* Engine::getButton(float yShift, Color color) {
    RectangleShape* button = new RectangleShape();
    button->setSize(Vector2f(200, 50));
    button->setFillColor(color);
    button->setPosition(100.0f, 40.0f + yShift);
    return button;
}

Font* Engine::getFont(string fontName) {
    Font* font = new Font();
    string logContent = "";
    if (!font->loadFromFile("fonts/"+fontName+".ttf"))
        setLogContent("[ERROR] " + getCurrentTime() + " Unsuccessfull " + fontName + " font load");
    else
        setLogContent("[INFO] " + getCurrentTime() + " " + fontName + " font was successfully loaded");
    return font;
}

string Engine::getFramePerSecondText(float currentTime) {
    float fps = 1.0f / currentTime;
    string fpsText = to_string(round(fps));
    size_t decimalPlacePos = fpsText.find(".000000");
    fpsText.erase(decimalPlacePos);
    return fpsText;
}

string Engine::getCurrentTime() {
    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timeStringBuffer[50] = "";
    ctime_s(timeStringBuffer, 50, &timeNow);
    string timeString = timeStringBuffer;
    timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.cend());
    return timeString;
}

int Engine::getRectNameWhenMouseIsPressedIn() {
    IntRect rect1(100, 60, 200, 50);
    IntRect rect2(100, 140, 200, 50);
    IntRect rect3(100, 220, 200, 50);
    IntRect rect4(100, 300, 200, 50);
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mouseBounds = Mouse::getPosition(*window);
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

Vector2f Engine::getGatePosition(string gateName) {
    Vector2u windowSize = window->getSize();
    Vector2u firstRes = Vector2u(1280, 720);
    Vector2u secondRes = Vector2u(1366, 768);
    Vector2u thirdRes = Vector2u(1600, 900);
    float firstResXPos = window->getSize().x * 0.84;
    float secondResXPos = window->getSize().x * 0.85;
    float thirdResXPos = window->getSize().x * 0.85;
    float firstResYPos = window->getSize().y * 0.30;
    float secondResYPos = window->getSize().y * 0.33;
    float thirdResYPos = window->getSize().y * 0.38;
    if (gateName == "left") 
        return (windowSize == firstRes) ? (Vector2f(50.0f, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(50.0f, secondResYPos)) : Vector2f(75.0f, thirdResYPos));
    else 
        return (windowSize == firstRes) ? (Vector2f(firstResXPos, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(secondResXPos, secondResYPos)) : Vector2f(thirdResXPos, thirdResYPos));
}

void Engine::setMenuBackground() {
    string fileName = "backgrounds/main/SG" + to_string(window->getSize().x) + "x" + to_string(window->getSize().y) + ".png";
    Texture backgroundTexture = createTextureFrom(fileName);
    Sprite backgroundSprite = createSpriteFrom(&backgroundTexture, Vector2f(0.0f, 0.0f));
    setMainBufferTexture(backgroundSprite);
    setSecondBufferTexture(backgroundSprite);
    handleBuffers();
}

void Engine::setGameBackground(string currentTime) {
    string fileName = "backgrounds/stadium/stadion" + to_string(window->getSize().x) + "x" + to_string(window->getSize().y) + ".png";
    Text fpsTextPlace = getText(Color::White);
    fpsTextPlace.setString(currentTime);
    Texture backgroundTexture = createTextureFrom(fileName);
    Texture rightGateTexture = createTextureFrom("elements/BramkaP.png");
    Texture leftGateTexture = createTextureFrom("elements/BramkaL.png");
    Texture fpsTexture = createTextureFrom(fpsTextPlace, Vector2i(100, 100), Color::Transparent);
    Sprite finallyBackgroundSprite;
    Sprite rightGateSprite = createSpriteFrom(&rightGateTexture, getGatePosition("right"));
    Sprite leftGateSprite = createSpriteFrom(&leftGateTexture, getGatePosition("left"));
    Sprite backgroundSprite = createSpriteFrom(&backgroundTexture, Vector2f(0.0f, 0.0f));
    Sprite fpsSprite = createSpriteFrom(&fpsTexture, Vector2f(0.0f, 0.0f));
    backgroundRenderTexture->clear(Color::Transparent);
    backgroundRenderTexture->draw(backgroundSprite);
    backgroundRenderTexture->draw(leftGateSprite);
    backgroundRenderTexture->draw(rightGateSprite);
    backgroundRenderTexture->draw(fpsSprite);
    backgroundRenderTexture->display();
    finallyBackgroundSprite.setTexture(backgroundRenderTexture->getTexture());
    setMainBufferTexture(finallyBackgroundSprite);
    setSecondBufferTexture(finallyBackgroundSprite);
    handleBuffers();
}

Texture Engine::createTextureFrom(Text text, Vector2i size, Color textureColor) {
    RenderTexture renderTexture;
    renderTexture.create(size.x, size.y);
    renderTexture.clear(textureColor);
    renderTexture.draw(text);
    renderTexture.display();
    Texture texture(renderTexture.getTexture());
    return texture;
}

Texture Engine::createTextureFrom(string fileName) {
    Texture texture;
    texture.loadFromFile(fileName);
    return texture;
}

Sprite Engine::createSpriteFrom(Texture* texture, Vector2f position) {
    Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setPosition(position.x, position.y);
    return sprite;
}

void Engine::serveWindowCloseEvent() {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed)
            window->close();
        if (event.type == Event::MouseMoved || event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed)
            breakClock.restart();
        if (event.type == Event::Resized) {
            FloatRect view(0, 0, event.size.width, event.size.height);
            window->setView(View(view));
        }
    }
}

void Engine::drawButtons() {
    RectangleShape* playButton = getButton(260, Color::Red);
    int rectName = getRectNameWhenMouseIsPressedIn();
    switch (rectName) {
        case RESOLUTION_1:
            resolution1Button = getButton(20, Color::Red);
            resolution2Button = getButton(100, Color::Green);
            resolution3Button = getButton(180, Color::Green);
        break;
        case RESOLUTION_2:
            resolution1Button = getButton(20, Color::Green);
            resolution2Button = getButton(100, Color::Red);
            resolution3Button = getButton(180, Color::Green);
        break;
        case RESOLUTION_3:
            resolution1Button = getButton(20, Color::Green);
            resolution2Button = getButton(100, Color::Green);
            resolution3Button = getButton(180, Color::Red);
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

void Engine::drawTexts() {
    Text resolution1 = getText(Color::White, "1280 x 720");
    Text resolution2 = getText(Color::White, "1366 x 768");
    Text resolution3 = getText(Color::White, "1600 x 900");
    Text startGame = getText(Color::White, "Uruchom gre");
    resolution1.setPosition(130, 70);
    resolution2.setPosition(130, 150);
    resolution3.setPosition(130, 230);
    startGame.setPosition(120, 310);
    window->draw(resolution1);
    window->draw(resolution2);
    window->draw(resolution3);
    window->draw(startGame);
}

void Engine::handleBuffers() {
    setFrameRateLimit();
    if (activeBuffer == "main") {
        secondBuffer.clear();
        secondBuffer.draw(Sprite(mainBuffer.getTexture()));
        secondBuffer.display();
        window->clear();
        window->draw(Sprite(secondBuffer.getTexture()));
        window->display();
        activeBuffer = "second";
    }
    else {
        mainBuffer.clear();
        mainBuffer.draw(Sprite(secondBuffer.getTexture()));
        mainBuffer.display();
        window->clear();
        window->draw(Sprite(mainBuffer.getTexture()));
        window->display();
        activeBuffer = "main";
    }
    fpsClock.restart();
}

void Engine::clearWindowToColor(Color color) {
    window->clear(color);
}

void Engine::clearSpriteToColor(Sprite& sprite, Color color) {
    sprite.setColor(color);
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

void Engine::saveLog() {
    fstream fileStream;
    fileStream.open("logs.log", ios::app);
    fileStream << logContent << endl;
    fileStream.close();
    cout << logContent << endl;
}

void Engine::testPrimitiveRenderer() {
    PrimitiveRenderer primitiveRenderer;
    //primitiveRenderer.drawRectangle(Vector2f(200.0f, 200.0f), Vector2f(100.0f, 100.0f), Color::White);
    //primitiveRenderer.drawCircle(50.0f, Vector2f(100.0f, 100.0f), Color::White);
    //primitiveRenderer.drawTriangle(25.0f, Vector2f(100.0f, 100.0f), Color::White);
    //primitiveRenderer.drawIncreasedLine(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 100.0f), Color::Blue); // m <=1
    //primitiveRenderer.drawIncreasedLine(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 200.0f), Color::Blue); // m przekracza 1
    //primitiveRenderer.drawLine(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 100.0f), Color::Blue); // zgadza się z m <=1 (linia renderowana przez mechanizm SFML)
    //primitiveRenderer.drawLine(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 200.0f), Color::Blue); // zgadza się z m przekracza 1 (linia renderowana przez mechanizm SFML)
    vector<LineSegment> lines;
    Point2D startPoint(5.0f, 5.0f);
    Point2D endPoint(100.0f, 5.0f);
    LineSegment line1(startPoint, endPoint);
    startPoint.setCoords(5.0f, 105.0f);
    endPoint.setCoords(100.0f, 105.0f);
    LineSegment line2(startPoint, endPoint);
    startPoint.setCoords(5.0f, 5.0f);
    endPoint.setCoords(5.0f, 105.0f);
    LineSegment line3(startPoint, endPoint);
    startPoint.setCoords(100.0f, 5.0f);
    endPoint.setCoords(100.0f, 105.0f);
    LineSegment line4(startPoint, endPoint);
    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);
    lines.push_back(line4);
    primitiveRenderer.drawPolygon(lines, Color::Black);
    //primitiveRenderer.borderRectFill(Point2D(17.0f, 8.0f), Color::Cyan, Color(0,0,0));
    //primitiveRenderer.drawBrokenLine(lines, Color::Blue);
    //primitiveRenderer.drawSymetricCircle(50, startPoint, Color::Blue);
    //primitiveRenderer.drawEllipse(50, 30, startPoint, Color::Red);
}

void Engine::testPoint2D() {
    Point2D point2D(75.0f, 100.0f);
    point2D.draw();
}

void Engine::testLineSegment() {
    Point2D startPoint(0.0f, 0.0f);
    Point2D endPoint(100.0f, 100.0f);
    LineSegment lineSegment(startPoint, endPoint);
    lineSegment.draw(Color::Black);
}

int main() {
    Engine::getInstance().activeWindowName = STARTUP_SETTINGS;
    Engine::getInstance().mainWindowSetup();
    return 0;
}