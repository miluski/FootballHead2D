#pragma once
#define _USE_MATH_DEFINES
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/**
 * @brief Wyliczenie reprezentujące nazwy okien.
 */
enum windowNames {STARTUP_SETTINGS, MENU, GAME, AUTHORS, GAME_OPTIONS, WINNER_SCREEN};

/**
 * @brief Wyliczenie reprezentujące nazwy prostokątów.
 */
enum rectNames {RESOLUTION_1, RESOLUTION_2, RESOLUTION_3, PLAY};

/**
* @brief Wyliczenie reprezentujące kierunek poruszania się piłki.
*/
enum directionNames {NORTH, SOUTH, WEST, EAST, SOUTH_WEST, NORTH_WEST, NORTH_EAST, SOUTH_EAST};

namespace Game {

    class Engine {

    public:

        int activeWindowName;
        static Engine& getInstance() {
            static Engine engine;
            return engine;
        }
        void mainWindowSetup();
        void setMainBufferTexture(Sprite textureSprite);
        void setSecondBufferTexture(Sprite textureSprite);
        RenderWindow* getMainWindow();
        void clearWindowToColor(Color color);
        void clearSpriteToColor(Sprite&, Color color);

        class GameObject {
        public:
            void setX(float x);
            void setY(float y);
            float getX();
            float getY();
        private:
            Vector2f actualPosition;
        };

        class DrawableObject : public virtual GameObject {
        public:
            void draw(void);
        };

        class TransformableObject : public virtual GameObject {
        public:
            void translate(Vector2f position);
            void rotate(float angle);
            void scale(Vector2f scale);
        };

        class ShapeObject : public DrawableObject, TransformableObject {
        public:
            virtual void draw() {};
            virtual void translate(Vector2f position) {};
            virtual void rotate(float angle) {};
            virtual void scale(Vector2f scale) {};
            void setColor(Color color) {};
            Color getColor() {};
        };

        class Rectangle : public ShapeObject {
        public:
            Rectangle();
            Rectangle(Vector2f size);
            virtual void draw();
            virtual void translate(Vector2f position);
            virtual void rotate(float angle);
            virtual void scale(Vector2f scale);
            virtual void setColor(Color color);
            virtual Color getColor();
        private:
            RectangleShape rectangle;
        };

        class Circle : public ShapeObject {
        public:
            Circle(float radius);
            virtual void draw();
            virtual void translate(Vector2f position);
            virtual void rotate(float angle);
            virtual void scale(Vector2f scale);
            virtual void setColor(Color color);
            virtual Color getColor();
        private:
            CircleShape circle;
        };

        class Triangle : public ShapeObject {
        public:
            Triangle(float radius);
            virtual void draw();
            virtual void translate(Vector2f position);
            virtual void rotate(float angle);
            virtual void scale(Vector2f scale);
            virtual void setColor(Color color);
            virtual Color getColor();
        private:
            CircleShape triangle;
        };

        class BitmapHandler {
        public:
            BitmapHandler();
            BitmapHandler(string fileName);
            BitmapHandler(Text text, Vector2i size, Color textureColor);
            void createBitmap(Vector2f size);
            void loadBitmapFrom(string fileName);
            void createBitmapFrom(Text text, Vector2i size, Color textureColor);
            BitmapHandler copy();
            void saveBitmapTo(string fileName);
            void deleteBitmap();
            Texture bitmap;
        private:
            void setBitmap(Texture bitmap);
        };

        class AnimatedObject : public virtual GameObject {
        public:
            void animate();
        };

        class Player : public virtual GameObject {
        public:
            bool isShooting = false;
            bool isFreezed = false;
            bool isDisabled = false;
            FloatRect topRect;
            FloatRect leftRect;
            FloatRect rightRect;
            FloatRect shoeRect;
            void setActualSpeed(float speed);
            void setPlayerBitmap(BitmapHandler bitmap);
            void setPlayerDisabledBitmap(BitmapHandler bitmap);
            void setPlayerFreezedBitmap(BitmapHandler bitmap);
            void setActualPosition(Vector2f position, string positionSite);
            float getActualSpeed();
            Vector2f getActualPosition();
            BitmapHandler getPlayerBitmap();
        private:
            int goals = 0;
            float actualSpeed = 0.0f;
            Vector2f position;
            BitmapHandler playerBitmap;
            BitmapHandler playerFreezedBitmap;
            BitmapHandler playerDisabledBitmap;
        };

        class Ball : public virtual GameObject {
        public:
            void setActualSpeed(float speed);
            void setBallBitmap(BitmapHandler bitmap);
            void setActualPosition(Vector2f position);
            float getActualSpeed();
            Vector2f getActualPosition();
            BitmapHandler getBallBitmap();
        private:
            float actualSpeed = 0.0f;
            Vector2f position;
            BitmapHandler ballBitmap;
        };

        class BitmapObject : public DrawableObject {
        public:
            virtual void draw();
            Sprite getSprite();
            Sprite spriteObject;
        };

        class SpriteObject : public BitmapObject, AnimatedObject {
        public:
            SpriteObject();
            SpriteObject(Texture* bitmap, Vector2f position, Vector2f scale);
            void createSpriteFrom(Texture* bitmap, Vector2f position, Vector2f scale);
            void createSpriteFrom(Texture* bitmap[], int bitmapArraySize, Vector2f positions[], Vector2f scales[]);
            void setCollisionRect(IntRect collisionRect);
            virtual void animate(BitmapHandler bitmap, Player* player);
        };

    private:

        string activeBuffer = "second";
        string lastTouchBallPlayerName;
        string leftPlayerSkin = "skin1";
        string rightPlayerSkin = "skin1";
        string stadiumSkin = "stadium1";
        string endText;
        bool centered = false;
        bool pause = false;
        bool mute = false;
        bool isPreviousFromThisWindow = false;
        bool endedGame = false;
        bool isEffectActive = false;
        int ballMoveDirection;
        int leftPlayerPoints;
        int rightPlayerPoints;
        int goalCountRequiredToWin = 1;
        int secondsRequiredToEndTheGame = 60;
        int winnerNumber = 0;
        int effectNumber = 1;
        float totalElapsedTime = 0.0f;
        float endTextX;
        Vector2u* windowSize = new Vector2u(400, 400);
        RenderWindow* window = new RenderWindow(VideoMode(windowSize->x, windowSize->y), "", Style::Titlebar | Style::Close);
        RenderTexture* backgroundRenderTexture = new RenderTexture();
        Rectangle resolution1Button = getButton(20, Color::Green, Vector2f(200, 50));
        Rectangle resolution2Button = getButton(100, Color::Green, Vector2f(200, 50));
        Rectangle resolution3Button = getButton(180, Color::Green, Vector2f(200, 50));
        Player leftPlayer;
        Player rightPlayer;
        Ball ball;
        BitmapHandler backgroundTexture;
        BitmapHandler leftPlayerBitmap;
        BitmapHandler rightPlayerBitmap;
        BitmapHandler leftPlayerShot;
        BitmapHandler rightPlayerShot;
        BitmapHandler leftPlayerFreezed;
        BitmapHandler leftPlayerDisabled;
        BitmapHandler rightPlayerFreezed;
        BitmapHandler rightPlayerDisabled;
        BitmapHandler iceCubeBitmap;
        BitmapHandler leftBrokenLegBitmap;
        BitmapHandler rightBrokenLegBitmap;
        Color menuTextColor = Color::White;
        Color pauseTextColor = Color::White;
        Color startTextColor = Color::White;
        Color optionsTextColor = Color::White;
        Color authorTextColor = Color::White;
        Color exitTextColor = Color::White;
        Color player1HallandTextColor = Color::Red;
        Color player1MbappeTextColor = Color::White;
        Color player1MessiTextColor = Color::White;
        Color player1RonaldoTextColor = Color::White;
        Color player2HallandTextColor = Color::Red;
        Color player2MbappeTextColor = Color::White;
        Color player2MessiTextColor = Color::White;
        Color player2RonaldoTextColor = Color::White;
        Color stadion1TextColor = Color::Red;
        Color stadion2TextColor = Color::White;
        Color timer1TextColor = Color::Red;
        Color timer3TextColor = Color::White;
        Color timer5TextColor = Color::White;
        Color timer10TextColor = Color::White;
        Color limit1GoalTextColor = Color::Red;
        Color limit3GoalTextColor = Color::White;
        Color limit5GoalTextColor = Color::White;
        Color limit10GoalTextColor = Color::White;
        Music music;
        Music goalMusic;
        Music whistleMusic;
        Music finalWhistleMusic;
        Music winnerScreenMusic;
        Vector2i windowPosition;
        Vector2f effectPosition;
        Vector2f effectSize;
        RenderTexture mainBuffer;
        RenderTexture secondBuffer;
        Clock clock;
        Font font;
        string logContent;
        Clock breakClock;
        Clock fpsClock;
        Clock goalTimer;
        Clock gameTimer;
        Clock effectExistingTimer;
        Clock effectDurationAtPlayerTimer;
        void menuWindowSetup();
        void settingsWindowSetup();
        void gameWindowSetup(string currentTime);
        void authorsWindowSetup();
        void gameOptionsWindowSetup();
        void winnerWindowSetup();
        void setWidthAndHeight(Rectangle resolution1Button, Rectangle resolution2Button, Rectangle resolution3Button);
        void setFrameRateLimit();
        void setLogContent(string logContent);
        Text getText(Color color, string content);
        Text getText(Color color, int fontSize, string content);
        Rectangle getButton(float yShift, Color color, Vector2f size);
        Rectangle getButton(Color color, Vector2f size, Vector2f position);
        Font* getFont(string fontName);
        string getFramePerSecondText(float currentTime);
        string getCurrentTime();
        Vector2f getGatePosition(string gateName);
        Vector2f getPlayerPosition(string playerName);
        bool isPositionInCollisionRects(Vector2f position);
        Vector2f getEffectPosition();
        int getRectNameWhenMouseIsPressedIn();
        int getEffectNumber();
        int getRandomPlayerNumber();
        string getLoudSpeakerFileName();
        string getArrowFileName();
        void setMenuBackground();
        void setGameBackground(string currentTime);
        void checkRectsActions();
        void checkIsCollisionWithEffect();
        bool checkIsGoalAtLeftGate();
        bool checkIsGoalAtRightGate();
        bool checkIsCollisionWithPlayer();
        void moveBall();
        void checkArrowRectActions();
        void checkMenuRectsActions();
        void checkGameOptionsRectsActions();
        void checkPlayerActions(SpriteObject player1, SpriteObject player2);
        void checkCollisions();
        void serveWindowCloseEvent();
        void drawButtons();
        void drawTexts();
        void gameOptionsChoices();
        void handleBuffers();
        bool validateLogContentFormat();
        void saveLog();
        void savePoints(string pointsMessage);
        void testPrimitiveRenderer();
        void testPoint2D();
        void testLineSegment();
        void testRectFill();
    };

    class Point2D {
    public:
        Point2D();
        Point2D(float x, float y);
        Point2D(Color pixelColor, float x, float y);
        float getX();
        float getY();
        Color getPixelColor();
        void setPixelColor(Color pixelColor);
        void setCoords(float x, float y);
        void draw();
    private:
        Color pixelColor = Color::White;
        float x;
        float y;
    };

    class LineSegment {
    public:
        LineSegment(Point2D startPoint, Point2D endPoint);
        Point2D getStartPoint();
        Point2D getEndPoint();
        void setStartPoint(Point2D startPoint);
        void setEndPoint(Point2D endPoint);
        void draw(Color color);
        void drawIncreased(Color color);
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
        bool isLinesCrossing(LineSegment line1, LineSegment line2);
        void drawPolygon(vector<LineSegment> lines, Color color);
        void borderRectFill(Point2D point, Color fillColor, Color borderColor);
        void floodRectFill(Point2D point, Color fillColor, Color backgroundColor);
    };
}
