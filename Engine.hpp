#pragma once
#define _USE_MATH_DEFINES
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum windowNames {STARTUP_SETTINGS=0, MENU=1, GAME=2, GAME_HELPER=3};
enum rectNames {RESOLUTION_1=1, RESOLUTION_2=2, RESOLUTION_3=3, PLAY=4};

class Engine {
public:

    int activeWindowName;

    static Engine& getInstance() {
        static Engine engine;
        return engine;
    }

    void mainWindowSetup();
    void setSecondBufferTexture(Sprite* textureSprite, Vector2u textureSize);
    RenderWindow* getMainWindow();
    Texture* createTextureFrom(Text* text, Vector2i size, Color textureColor);
    Texture* createTextureFrom(Image* image, Vector2i size);
    void clearWindowToColor(Color color);
    void clearSpriteToColor(Sprite&, Color color);

private:

    string activeBuffer = "main";
    bool centered = false;
    Vector2u* windowSize = new Vector2u(400, 400);
    RenderWindow* window = new RenderWindow(VideoMode(windowSize->x, windowSize->y), "", Style::Titlebar | Style::Close);
    RectangleShape* resolution1Button = getButton(20, Color::Green);
    RectangleShape* resolution2Button = getButton(100, Color::Green);
    RectangleShape* resolution3Button = getButton(180, Color::Green);
    Vector2i windowPosition;
    RenderTexture mainBuffer;
    RenderTexture secondBuffer;
    Clock clock;
    Font font;
    string logContent;
    Clock breakClock;

    void menuWindowSetup();
    void settingsWindowSetup();
    void gameWindowSetup(float currentTime);
    void gameHelperWindowSetup();
    void setWidthAndHeight(RectangleShape* resolution1Button, RectangleShape* resolution2Button, RectangleShape* resolution3Button);
    void setFrameRateLimit();
    void setLogContent(string logContent);
    Text* getText();
    Text* getText(string content);
    RectangleShape* getButton(float yShift, Color color);
    Font* getArialFont();
    string getFramePerSecondText(float currentTime);
    string getCurrentTime();
    int getRectNameWhenMouseIsPressedIn();
    void serveWindowCloseEvent();
    void drawButtons();
    void drawTexts();
    void handleBuffers();
    bool validateLogContentFormat();
    void saveLog();

    void testPrimitiveRenderer();
    void testPoint2D();
    void testLineSegment();

};

class Point2D {
public:
    float getX();
    float getY();
    void setCoords(float x, float y);
    void drawPoint();
private:
    float x;
    float y;
};

class LineSegment {
public:
    Point2D getStartPoint();
    Point2D getEndPoint();
    void setStartPoint(Point2D startPoint);
    void setEndPoint(Point2D endPoint);
    void drawLine();
    void drawIncreasedLine();
private:
    Point2D startPoint;
    Point2D endPoint;
};

class PrimitiveRenderer {
public:
    void drawRectangle(Vector2f size, Vector2f position, Color color);
    void drawCircle(float radius, Vector2f position, Color color);
    void drawSymetricCircle(float radius, Point2D startPoint, Color color);
    void drawTriangle(float radius, Vector2f position, Color color);
    void drawIncreasedLine(Vector2f startCoords, Vector2f endCoords, Color color);
    void drawLine(Vector2f startCoords, Vector2f endCoords, Color color);
    void drawBrokenLine(vector<LineSegment> lines, Color color);
    void drawEllipse(float radiusX, float radiusY, Point2D startPoint, Color color);
    void drawPolygon(vector<LineSegment> lines, Color color);
};