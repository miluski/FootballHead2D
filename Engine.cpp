#include "Engine.hpp"

using namespace Game;

/**
 * @brief Funkcja ustawia główne okno silnika gry.
 *
 * Ta funkcja inicjuje okno główne gry, konfiguruje różne elementy gry
 * i wchodzi w pętlę zarządzającą różnymi oknami w oparciu o bieżący stan.
 */
void Engine::mainWindowSetup() {
    font = *getFont("arial");
    setFrameRateLimit();
    Image iconImage;
    iconImage.loadFromFile("elements/game/Pilka.png");
    window->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());
    window->setVerticalSyncEnabled(true);
    string fps = "";
    while (window->isOpen()) {
        float elapsed = breakClock.getElapsedTime().asSeconds();
        float currentTime = fpsClock.restart().asSeconds();
        fps = getFramePerSecondText(currentTime);
        if (elapsed > 300)
            window->close();
        serveWindowCloseEvent();
        switch (activeWindowName) {
            case STARTUP_SETTINGS:
                settingsWindowSetup();
            break;
            case MENU:
                sleep(milliseconds(10));
                menuWindowSetup();
            break;
            case GAME:
                isPreviousFromThisWindow = false;
                gameWindowSetup(fps);
            break;
            case AUTHORS:
                isPreviousFromThisWindow = true;
                authorsWindowSetup();
            break;
            case GAME_OPTIONS:
                isPreviousFromThisWindow = true;
                gameOptionsWindowSetup();
            break;
            case WINNER_SCREEN:
                isPreviousFromThisWindow = false;
                winnerWindowSetup();
            break;
        }
    }
}

/**
 * @brief Funkcja ustawienia okna gry.
 *
 * Metoda odpowiedzialna za konfigurację okna gry, ustawienie tytułu,
 * wyczyszczenie okna do koloru czarnego, narysowanie przycisków i tekstów,
 * oraz wyświetlenie okna.
 */
void Engine::settingsWindowSetup() {
    window->setTitle("Ustawienia gry");
    getInstance().clearWindowToColor(Color::Black);
    drawButtons();
    drawTexts();
    window->display();
}

/**
 * @brief Funkcja inicjalizująca menu główne gry.
 *
 * Metoda odpowiedzialna za konfigurację okna menu głównego, ustawienie tytułu, narysowanie przycisków i tekstów,
 * oraz wyświetlenie okna.
 */
void Engine::menuWindowSetup() {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        window->setTitle("Menu");
        font = *getFont("Pixellari");
        window->setSize(*windowSize);
        mainBuffer.create(windowSize->x, windowSize->y);
        secondBuffer.create(windowSize->x, windowSize->y);
        backgroundRenderTexture->create(window->getSize().x, window->getSize().y);
        if (!mute && !isPreviousFromThisWindow) {
            music.openFromFile("sounds/menu_music.wav");
            music.play();
        }
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        string fileName = "backgrounds/main/SG" + to_string(window->getSize().x) 
            + "x" + to_string(window->getSize().y) + ".png";
        backgroundTexture.loadBitmapFrom(fileName);
        centered = true;
    }
    else 
        setMenuBackground();
    if (music.getStatus() != Music::Status::Playing && !mute)
        music.play();
}

/**
 * @brief Funkcja konfiguruje tekstury i rozmieszcza elementy na ekranie.
 *
 * Ta funkcja inicjuje różne elementy okna gry, w tym bitmapy graczy, czcionki,
 * tekstury tła, muzyka i rozmiar okna. Zarządza też rozmieszczeniem wszystkich elementów na ekranie
 *
 * @param currentTime Bieżący czas używany podczas konfigurowania gry.
 */
void Engine::gameWindowSetup(string currentTime) {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        if (endedGame) {
            gameTimer.restart();
            endedGame = false;
        }
        string fileName = "backgrounds/stadium/" + stadiumSkin + "/stadion" + to_string(window->getSize().x) 
            + "x" + to_string(window->getSize().y) + ".png";
        BitmapHandler ballBitmap("elements/game/Pilka.png");
        leftPlayerBitmap.loadBitmapFrom("elements/game/leftPlayer/" + leftPlayerSkin + "/Haaland.png");
        rightPlayerBitmap.loadBitmapFrom("elements/game/rightPlayer/" + rightPlayerSkin + "/Ymbape.png");
        leftPlayerShot.loadBitmapFrom("elements/game/leftPlayer/" + leftPlayerSkin + "/Haaland_strzal.png");
        rightPlayerShot.loadBitmapFrom("elements/game/rightPlayer/" + rightPlayerSkin + "/Ymbape_strzal.png");
        leftPlayerFreezed.loadBitmapFrom("elements/game/leftPlayer/" + leftPlayerSkin + "/Haaland_zamrozony.png");
        rightPlayerFreezed.loadBitmapFrom("elements/game/rightPlayer/" + rightPlayerSkin + "/Ymbape_zamrozony.png");
        leftPlayerDisabled.loadBitmapFrom("elements/game/leftPlayer/" + leftPlayerSkin + "/Haaland_zlamany.png");
        rightPlayerDisabled.loadBitmapFrom("elements/game/rightPlayer/" + rightPlayerSkin + "/Ymbape_zlamany.png");
        iceCubeBitmap.loadBitmapFrom("elements/game/lod.png");
        leftBrokenLegBitmap.loadBitmapFrom("elements/game/NogaBandazL.png");
        rightBrokenLegBitmap.loadBitmapFrom("elements/game/NogaBandazP.png");
        backgroundTexture.loadBitmapFrom(fileName);
        font = *getFont("Pixellari");
        music.stop();
        window->setTitle("FootballHead2D");
        window->setSize(*windowSize);
        setFrameRateLimit();
        backgroundRenderTexture->create(window->getSize().x, window->getSize().y);
        music.openFromFile("sounds/stadium_crowd.wav");
        if(!mute)
            music.play();
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        leftPlayer.setPlayerBitmap(leftPlayerBitmap);
        rightPlayer.setPlayerBitmap(rightPlayerBitmap);
        ball.setBallBitmap(ballBitmap);
        leftPlayer.setActualSpeed(10.0f);
        rightPlayer.setActualSpeed(10.0f);
        ball.setActualSpeed(10.5f);
        leftPlayer.setActualPosition(getPlayerPosition("Haaland"), "left");
        rightPlayer.setActualPosition(getPlayerPosition("Ymbape"), "right");
        ball.setActualPosition(Vector2f((window->getSize().x) / 2.12f, (window->getSize().y) / 5.0f));
        whistleMusic.openFromFile("sounds/whistle.wav");
        whistleMusic.play();
        ballMoveDirection = SOUTH;
        centered = true;
    }
    else 
        setGameBackground(currentTime);
    if (music.getStatus() != Music::Status::Playing && !pause && !mute && !endedGame)
        music.play();
}

/**
 * @brief Funkcja ustawia okno autorów gry.
 *
 * Ta funkcja konfiguruje okno autorów gry, ustawiając jego limit liczby klatek na sekundę,
 * umieszczenie go na środku pulpitu (jeśli jeszcze okno nie jest wyśrodkowane) i ustawienie
 * tytuł okna na „Authors”. Dodatkowo dostosowuje rozmiar okna w oparciu o
 * podaną rozdzielczość.
 */
void Engine::authorsWindowSetup() {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        string fileName = "backgrounds/authors/autorzy" + to_string(window->getSize().x) + "x" + to_string(window->getSize().y) + ".png";
        setFrameRateLimit();
        window->setTitle("Autorzy");
        window->setSize(*windowSize);
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        backgroundTexture.loadBitmapFrom(fileName);
        centered = true;
    }
    checkArrowRectActions();
    BitmapHandler arrowBitmap(getArrowFileName());
    Texture* bitmapArray[2] = { &backgroundTexture.bitmap, &arrowBitmap.bitmap };
    Vector2f positions[2] = { Vector2f(0.0f, 0.0f), Vector2f((window->getSize().x) / 1.075f, 20.0f) };
    Vector2f scales[2] = { Vector2f(1.0f, 1.0f), Vector2f(0.5f, 0.5f) };
    SpriteObject background;
    background.createSpriteFrom(bitmapArray, 2, positions, scales);
    background.draw();
}

void Engine::gameOptionsWindowSetup() {                                                                                 //tutaj robic
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        string fileName = "backgrounds/settings/ustawieniatlo" + to_string(window->getSize().x) + "x" + to_string(window->getSize().y) + ".png";
        setFrameRateLimit();
        window->setTitle("Ustawienia gry");
        font = *getFont("Pixellari");
        window->setSize(*windowSize);
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2, (desktop.height - windowSize->y) / 2));
        backgroundTexture.loadBitmapFrom(fileName);
        centered = true;
    }
    checkArrowRectActions();
    checkGameOptionsRectsActions();
    BitmapHandler arrowBitmap(getArrowFileName());
    BitmapHandler chosePlayer1Bitmap(getText(startTextColor, 52, "Wybor skina gracza 1"), Vector2i(500, 60), Color::Transparent);
    BitmapHandler player1Halland(getText(player1HallandTextColor, 52, "Haaland"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player1Mbappe(getText(player1MbappeTextColor, 52, "Mbappe"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player1Messi(getText(player1MessiTextColor, 52, "Messi"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player1Ronaldo(getText(player1RonaldoTextColor, 52, "Ronaldo"), Vector2i(200, 60), Color::Transparent);

    BitmapHandler chosePlayer2Bitmap(getText(startTextColor, 52, "Wybor skina gracza 2"), Vector2i(500, 60), Color::Transparent);
    BitmapHandler player2Halland(getText(player2HallandTextColor, 52, "Haaland"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player2Mbappe(getText(player2MbappeTextColor, 52, "Mbappe"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player2Messi(getText(player2MessiTextColor, 52, "Messi"), Vector2i(200, 60), Color::Transparent);
    BitmapHandler player2Ronaldo(getText(player2RonaldoTextColor, 52, "Ronaldo"), Vector2i(200, 60), Color::Transparent);

    BitmapHandler choseStadionBitmap(getText(startTextColor, 52, "Wybor stadionu"), Vector2i(500, 60), Color::Transparent);
    BitmapHandler stadion1(getText(stadion1TextColor, 52, "Stadion 1"), Vector2i(300, 60), Color::Transparent);
    BitmapHandler stadion2(getText(stadion2TextColor, 52, "Stadion 2"), Vector2i(300, 60), Color::Transparent);
    BitmapHandler stadion3(getText(stadion3TextColor, 52, "Stadion 3"), Vector2i(300, 60), Color::Transparent);

    BitmapHandler choseGameTimeBitmap(getText(startTextColor, 52, "Wybor dlugosci meczu"), Vector2i(520, 60), Color::Transparent);
    BitmapHandler timer1Min(getText(timer1TextColor, 52, "1 Min"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler timer3Min(getText(timer3TextColor, 52, "3 Min"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler timer5Min(getText(timer5TextColor, 52, "5 Min"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler timer10Min(getText(timer10TextColor, 52, "10 Min"), Vector2i(170, 60), Color::Transparent);

    BitmapHandler choseGameGoalLimitBitmap(getText(startTextColor, 52, "Wybor limitu goli"), Vector2i(500, 60), Color::Transparent);
    BitmapHandler limit1Goal(getText(limit1GoalTextColor, 52, "1 Goli"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler limit3Goal(getText(limit3GoalTextColor, 52, "3 Goli"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler limit5Goal(getText(limit5GoalTextColor, 52, "5 Goli"), Vector2i(170, 60), Color::Transparent);
    BitmapHandler limit10Goal(getText(limit10GoalTextColor, 52, "10 Goli"), Vector2i(170, 60), Color::Transparent);
    
    Texture* bitmapArray[26] = { &backgroundTexture.bitmap, &arrowBitmap.bitmap, &chosePlayer1Bitmap.bitmap, &player1Halland.bitmap,
        &player1Mbappe.bitmap, &player1Messi.bitmap, &player1Ronaldo.bitmap,
        &chosePlayer2Bitmap.bitmap, &player2Halland.bitmap,
        &player2Mbappe.bitmap, &player2Messi.bitmap, &player2Ronaldo.bitmap,
        &choseStadionBitmap.bitmap, &stadion1.bitmap,&stadion2.bitmap,&stadion3.bitmap,
        &choseGameTimeBitmap.bitmap,&timer1Min.bitmap,&timer3Min.bitmap,
        &timer5Min.bitmap,&timer10Min.bitmap,
        &choseGameGoalLimitBitmap.bitmap,&limit1Goal.bitmap,&limit3Goal.bitmap,
        &limit5Goal.bitmap,&limit10Goal.bitmap
    };


    Vector2f positions[26] = { Vector2f(0.0f, 0.0f), Vector2f((window->getSize().x) / 1.075f, 20.0f), 
        Vector2f((window->getSize().x) / 3.25f, 20.0f), 
        Vector2f((window->getSize().x) / 6.0f, 90.0f),
        Vector2f((window->getSize().x) / 2.9f, 90.0f), 
        Vector2f((window->getSize().x) / 1.9f, 90.0f),
        Vector2f((window->getSize().x) / 1.5f, 90.0f),

        Vector2f((window->getSize().x) / 3.25f, 170.0f),
        Vector2f((window->getSize().x) / 6.0f, 230.0f),
        Vector2f((window->getSize().x) / 2.9f, 230.0f),
        Vector2f((window->getSize().x) / 1.9f, 230.0f),
        Vector2f((window->getSize().x) / 1.5f, 230.0f),

        Vector2f((window->getSize().x) / 2.7f, 310.0f),
        Vector2f((window->getSize().x) / 5.9f, 370.0f),
        Vector2f((window->getSize().x) / 2.4f, 370.0f),
        Vector2f((window->getSize().x) / 1.5f, 370.0f),

        Vector2f((window->getSize().x) / 3.2f, 450.0f),
        Vector2f((window->getSize().x) / 5.5f, 510.0f),
        Vector2f((window->getSize().x) / 2.85f, 510.0f),
        Vector2f((window->getSize().x) / 1.9f, 510.0f),
        Vector2f((window->getSize().x) / 1.45f, 510.0f),

        Vector2f((window->getSize().x) / 3.0f, 580.0f),
        Vector2f((window->getSize().x) / 5.5f, 640.0f),
        Vector2f((window->getSize().x) / 2.85f, 640.0f),
        Vector2f((window->getSize().x) / 1.9f, 640.0f),
        Vector2f((window->getSize().x) / 1.45f, 640.0f),
    };
    
    Vector2f scales[26] = { Vector2f(1.0f, 1.0f), Vector2f(0.5f, 0.5f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),
        Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),
        Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),  Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),  Vector2f(1.0f, 1.0f),
        Vector2f(1.0f, 1.0f),Vector2f(1.0f, 1.0f),Vector2f(1.0f, 1.0f),Vector2f(1.0f, 1.0f),Vector2f(1.0f, 1.0f),Vector2f(1.0f, 1.0f),
    };


    SpriteObject background;
    background.createSpriteFrom(bitmapArray, 26, positions, scales);
    background.draw();
}


void Engine::winnerWindowSetup() {
    VideoMode desktop = VideoMode::getDesktopMode();
    if (!centered) {
        winnerScreenMusic.openFromFile("sounds/winner.wav");
        font = *getFont("Pixellari");
        endText = "R E M I S!";
        window->setTitle("Remis!");
        endTextX = (window->getSize().x) / 2.60f;
        switch (winnerNumber) {
            case 1:
                if(!mute)
                    winnerScreenMusic.play();
                window->setTitle("Zwyciestwo!");
                endText = "G R A C Z  1  W Y G R A L";
                endTextX = (window->getSize().x) / 4.55f;
            break;
            case 2:
                if (!mute)
                    winnerScreenMusic.play();
                window->setTitle("Zwyciestwo!");
                endText = "G R A C Z  2  W Y G R A L";
                endTextX = (window->getSize().x) / 4.55f;
            break;
        }
        string fileName = "backgrounds/winner/winektlo" + to_string(window->getSize().x) + "x" + to_string(window->getSize().y) + ".png";
        setFrameRateLimit();
        window->setSize(*windowSize);
        window->setPosition(Vector2i((desktop.width - windowSize->x) / 2.0f, (desktop.height - windowSize->y) / 2.0f));
        backgroundRenderTexture->clear();
        backgroundTexture.loadBitmapFrom(fileName);
        centered = true;
    }
    checkArrowRectActions();
    BitmapHandler arrowBitmap(getArrowFileName());
    BitmapHandler endTextBitmap(getText(exitTextColor, 72, endText), Vector2i(1000, 100), Color::Transparent);
    Texture* bitmapArray[3] = { &backgroundTexture.bitmap, &arrowBitmap.bitmap, &endTextBitmap.bitmap };
    Vector2f positions[3] = { Vector2f(0.0f, 0.0f), Vector2f((window->getSize().x) / 1.075f, 20.0f),
                                Vector2f(endTextX, (window->getSize().y) / 2.2f)};
    Vector2f scales[3] = { Vector2f(1.0f, 1.0f), Vector2f(0.5f, 0.5f), Vector2f(1.0f, 1.0f) };
    SpriteObject background;
    background.createSpriteFrom(bitmapArray, 3, positions, scales);
    background.draw();
}

/**
 * @brief Funkcja Ustaw szerokość i wysokość okna gry w oparciu o wybrany przycisk rozdzielczości.
 *
 * Ta funkcja ustawia szerokość i wysokość okna gry w oparciu o wybraną przez gracza opcję
 *
 * @param rozdzielczość1Przycisk Przycisk reprezentujący pierwszą rozdzielczość (1280x720).
 * @param rozdzielczość2Button Przycisk reprezentujący drugą rozdzielczość (1366x768).
 * @param rozdzielczość3Przycisk Przycisk reprezentujący trzecią rozdzielczość (1600x900).
 */
void Engine::setWidthAndHeight(Rectangle resolution1Button, Rectangle resolution2Button,
    Rectangle resolution3Button) {
    if (resolution1Button.getColor() == Color::Red) {
        windowSize->x = 1280;
        windowSize->y = 720;
        getInstance().activeWindowName = MENU;
    }
    else if (resolution2Button.getColor() == Color::Red) {
        windowSize->x = 1366;
        windowSize->y = 768;
        getInstance().activeWindowName = MENU;
    }
    else if (resolution3Button.getColor() == Color::Red) {
        windowSize->x = 1600;
        windowSize->y = 900;
        getInstance().activeWindowName = MENU;
    }
}

/**
 * @brief Funkcja ustawia teksturę głównego bufora.
 *
 * Ta funkcja czyści główny bufor, rysuje na nim określoną teksturę,
 *, a następnie wyświetla bufor.
 *
 * @param teksturSprite Duszek reprezentujący teksturę do narysowania w głównym buforze.
 */
void Engine::setMainBufferTexture(Sprite textureSprite) {
    mainBuffer.clear();
    mainBuffer.draw(textureSprite);
    mainBuffer.display();
}

/**
 * @brief Funkcja ustawia teksturę w drugim buforze.
 *
 * Metoda ta przyjmuje obiekt Sprite reprezentujący teksturę i ustawia go w drugim buforze.
 *
 * @param teksturySprite Obiekt Sprite charakterystyczny teksturę, która może być ustawiona w drugim buforze.
 */
void Engine::setSecondBufferTexture(Sprite textureSprite) {
    secondBuffer.clear();
    secondBuffer.draw(textureSprite);
    secondBuffer.display();
}

/**
 * @brief Funkcja ogranicza liczbę klatek w grze.
 *
 * Metoda ta ogranicza liczbę klatek na sekunde w których działa gra.
 *
 */
void Engine::setFrameRateLimit() {
    window->setFramerateLimit(60);
}

/**
 * @brief Funkcja ustawia zawartość dziennika.
 *
 * Metoda ta ustawia nową zawartość dziennika na podstawie przekazanego ciągu znaków.
 * Następnie sprawdza poprawność formatu dziennika za pomocą metody validateLogContentFormat().
 * Jeśli format jest niepoprawny, generuje błąd i zapisuje go jako nową zawartość dziennika.
 * Ostatecznie, wywołuje metodę saveLog() w celu zapisania zawartości dziennika.
 *
 * @param logContent Nowa zawartość dla dziennika do ustawienia.
 */
void Engine::setLogContent(string logContent) {
    this->logContent = logContent;
    if (!validateLogContentFormat()) {
        string error = "[ERROR] " + getCurrentTime() + " Uncorrect log format";
        this->logContent = error;
    }
    saveLog();
}

/**
 * @brief Funkcja pobiera wskaźnik do głównego okna aplikacji.
 *
 *
 * @return Wskaźnik do obiektu klasy RenderWindow reprezentującego główne okno.
 */
RenderWindow* Engine::getMainWindow() {
    return window;
}

/**
 * @brief Funkcja tworząca obiekt tekstu z określonym kolorem i zawartością.
 *
 * @param color Kolor tekstu.
 * @param content Zawartość tekstu.
 * @return Obiekt tekstu gotowy do wyświetlenia.
 *
 * Tworzy obiekt tekstu, ustawiając mu odpowiednią czcionkę, kolor, zawartość,
 * oraz rozmiar znaków. Zwraca gotowy do użycia obiekt tekstu.
 */
Text Engine::getText(Color color, string content) {
    Text text;
    text.setFont(font);
    text.setFillColor(color);
    text.setString(content);
    text.setCharacterSize(28);
    return text;
}

/**
 * @brief Funkcja umożliwiająca utworzenie obiektu tekstowego o określonych właściwościach.
 *
 * Ta funkcja tworzy obiekt tekstowy o określonym kolorze, rozmiarze czcionki i zawartości.
 *
 * @param color Kolor tekstu.
 * @param FontSize Rozmiar czcionki tekstu.
 * @param content Treść tekstu.
 *
* @return Obiekt tekstowy o określonych właściwościach.
 */
Text Engine::getText(Color color, int fontSize, string content) {
    Text text;
    text.setFont(font);
    text.setFillColor(color);
    text.setString(content);
    text.setCharacterSize(fontSize);
    return text;
}

/**
 * @brief Funkcja tworząca prostokątny przycisk.
 *
 * @param yShift Przesunięcie w osi y dla umieszczenia przycisku.
 * @param color Kolor przycisku.
 * @param size Rozmiar przycisku.
 * @return Prostokąt reprezentujący przycisk.
 */
Engine::Rectangle Engine::getButton(float yShift, Color color, Vector2f size) {
    Rectangle button(size);
    button.setColor(color);
    button.translate(Vector2f(100.0f, 40.0f + yShift));
    return button;
}

/**
 * @brief Funkcja tworząca obiekt typu Rectangle reprezentujący przycisk.
 *
 * Funkcja tworzy obiekt typu Rectangle, który może być używany jako przycisk. Ustawia dla niego kolor, rozmiar i pozycję.
 *
 * @param color Kolor przycisku.
 * @param size Rozmiar przycisku (wektor 2D).
 * @param position Pozycja przycisku (wektor 2D).
 *
 * @return Zwraca obiekt Rectangle reprezentujący przycisk.
 */
Engine::Rectangle Engine::getButton(Color color, Vector2f size, Vector2f position) {
    Rectangle button(size);
    button.setColor(color);
    button.translate(position);
    return button;
}

/**
 * @brief Funkcja pobiera obiekt Font na podstawie podanej nazwy czcionki.
 *
 * Ta funkcja tworzy nowy obiekt Font i próbuje załadować plik czcionki o podanej nazwie
 * z katalogu „fonts/”. Generuje komunikaty dziennika wskazujące, czy
 * ładowanie czcionki powiodło się lub nie.
 *
* @param FontName Nazwa pliku czcionki (bez rozszerzenia) do załadowania.
 * @return Wskaźnik do załadowanego obiektu Font.
 */
Font* Engine::getFont(string fontName) {
    Font* font = new Font();
    string logContent = "";
    if (!font->loadFromFile("fonts/"+fontName+".ttf"))
        setLogContent("[ERROR] " + getCurrentTime() + " Unsuccessfull " + fontName + " font load");
    else
        setLogContent("[INFO] " + getCurrentTime() + " " + fontName + " font was successfully loaded");
    return font;
}

/**
 * @brief Funkcja generująca tekst reprezentujący liczbę klatek na sekundę (FPS).
 *
 * Funkcja ta przyjmuje aktualny czas trwania jednej klatki (currentTime) i oblicza
 * liczbę klatek na sekundę na podstawie odwrotności tego czasu.
 *
 * @param currentTime Aktualny czas trwania jednej klatki w sekundach.
 * @return Tekst reprezentujący liczbę klatek na sekundę.
 */
string Engine::getFramePerSecondText(float currentTime) {
    float fps = 1.0f / currentTime;
    string fpsText = to_string(round(fps));
    size_t decimalPlacePos = fpsText.find(".000000");
    fpsText.erase(decimalPlacePos);
    return fpsText;
}

/**
 * @brief Pobiera aktualny czas jako sformatowany ciąg znaków.
 *
 * Ta funkcja pobiera bieżący czas systemowy i formatuje go jako ciąg znaków.
 * Format obejmuje informację o dacie i godzinie oraz wynikowy ciąg znaków
 * jest czyszczone w celu usunięcia znaków nowej linii.
 *
 * @return Ciąg zawierający bieżący czas.
 */
string Engine::getCurrentTime() {
    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char timeStringBuffer[50] = "";
    ctime_s(timeStringBuffer, 50, &timeNow);
    string timeString = timeStringBuffer;
    timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.cend());
    return timeString;
}

/**
 * @brief Funkcja pobiera identyfikator prostokąta po naciśnięciu lewego przycisku myszy.
 *
 * Ta funkcja sprawdza, czy lewy przycisk myszy jest wciśnięty i zwraca
 * identyfikator prostokąta na podstawie pozycji myszy.
 *
 * @return Liczba całkowita reprezentująca identyfikator prostokąta po naciśnięciu myszki,
 * Lub 1, jeśli nie zostanie naciśnięty żaden prostokąt.
 */
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

/**
 * @brief Funkcja ustawiająca pozycję bramki w oknie gry.
 *
 * Ta funkcja oblicza i zwraca pozycję bramki na podstawie podanej nazwy bramki
 * i dla aktualnego rozmiaru okna.
 *
 * @param gateName Nazwa bramki („lewa” lub „prawa”).
 * @return Vector2f reprezentujący położenie bramki.
 */
Vector2f Engine::getGatePosition(string gateName) {
    Vector2u windowSize = window->getSize();
    Vector2u firstRes = Vector2u(1280, 720);
    Vector2u secondRes = Vector2u(1366, 768);
    Vector2u thirdRes = Vector2u(1600, 900);
    float firstResXPos = window->getSize().x * 0.84f;
    float secondResXPos = window->getSize().x * 0.85f;
    float thirdResXPos = window->getSize().x * 0.85f;
    float firstResYPos = window->getSize().y * 0.30f;
    float secondResYPos = window->getSize().y * 0.33f;
    float thirdResYPos = window->getSize().y * 0.38f;
    if (gateName == "left") 
        return (windowSize == firstRes) ? (Vector2f(50.0f, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(50.0f, secondResYPos)) : Vector2f(75.0f, thirdResYPos));
    else 
        return (windowSize == firstRes) ? (Vector2f(firstResXPos, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(secondResXPos, secondResYPos)) : Vector2f(thirdResXPos, thirdResYPos));
}

/**
 * @brief Funkcja pobiera pozycję gracza na podstawie jego nazwy i bieżącego rozmiaru okna.
 *
 * Ta funkcja oblicza i zwraca pozycję gracza w oknie gry
 * na podstawie nazwy gracza i aktualnego rozmiaru okna.
 *
 * @param playerName Nazwa gracza.
 * @return Vector2f reprezentujący pozycję gracza.
 */
Vector2f Engine::getPlayerPosition(string playerName) {
    Vector2u windowSize = window->getSize();
    Vector2u firstRes = Vector2u(1280, 720);
    Vector2u secondRes = Vector2u(1366, 768);
    Vector2u thirdRes = Vector2u(1600, 900);
    float firstResXPos = window->getSize().x * 0.68f;
    float secondResXPos = window->getSize().x * 0.68f;
    float thirdResXPos = window->getSize().x * 0.69f;
    float firstResYPos = window->getSize().y * 0.50f;
    float secondResYPos = window->getSize().y * 0.53f;
    float thirdResYPos = window->getSize().y * 0.56f;
    if (playerName == "Haaland")
        return (windowSize == firstRes) ? (Vector2f(275.0f, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(280.0f, secondResYPos)) : Vector2f(330.0f, thirdResYPos));
    else
        return (windowSize == firstRes) ? (Vector2f(firstResXPos, firstResYPos)) : (
            (windowSize == secondRes) ? (Vector2f(secondResXPos, secondResYPos)) : Vector2f(thirdResXPos, thirdResYPos));
}

/**
 * @brief Funkcja określa czy muzyka została wyciszona czy włączona na podstawie interakcji myszy.
 *
 * Obraz głośnika w menu zmienia się w zależności od pozycji myszy i kliknięć przycisków.
 *
 * @return Nazwa pliku obrazu głośnika włączonego/wycziszonego.
 */
string Engine::getLoudSpeakerFileName() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect loudSpeakerRect(Vector2f((window->getSize().x) / 1.05f, 20.0f), Vector2f(60.0f, 55.0f));
    if (loudSpeakerRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left) && !mute) {
            music.pause();
            mute = true;
            sleep(seconds(0.25f));
            return "elements/menu/glosnikMute.png";
        }
        if (Mouse::isButtonPressed(Mouse::Left) && mute) {
            music.play();
            mute = false;
            sleep(seconds(0.25f));
            return "elements/menu/glosnik.png";
        }
        return "elements/menu/glosnikMute.png";
    }
    else if (!mute)
        return "elements/menu/glosnik.png";
    else if (mute)
        return "elements/menu/glosnikMute.png";
    return "elements/menu/glosnik.png";
}

string Engine::getArrowFileName() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect arrowRect(Vector2f((window->getSize().x) / 1.075f, 20.0f), Vector2f(60.0f, 55.0f));
    if (arrowRect.contains(mouseX, mouseY)) 
        return "elements/menu/strzalkaHover.png";
    else
        return "elements/menu/strzalka.png";
}

/**
 * @brief Funkcja ustawia tło ekranu menu.
 *
 * Ta funkcja ustawia tło ekranu menu poprzez tworzenie i pozycjonowanie
 * różnych przycisków, bitmap i innych elementów graficznych.
 */
void Engine::setMenuBackground() {
    checkMenuRectsActions();
    BitmapHandler startTextBitmap(getText(startTextColor, 52, "S T A R T"), Vector2i(220, 60), Color::Transparent);
    BitmapHandler optionsTextBitmap(getText(optionsTextColor, 52, "O P C J E"), Vector2i(220, 60), Color::Transparent);
    BitmapHandler authorTextBitmap(getText(authorTextColor, 52, "A U T O R Z Y"), Vector2i(350, 60), Color::Transparent);
    BitmapHandler exitTextBitmap(getText(exitTextColor, 52, "W Y J S C I E"), Vector2i(350, 60), Color::Transparent);
    BitmapHandler loudSpeakerBitmap(getLoudSpeakerFileName());
    Texture* bitmapArray[6] = { &backgroundTexture.bitmap, &startTextBitmap.bitmap, &optionsTextBitmap.bitmap, &authorTextBitmap.bitmap, &exitTextBitmap.bitmap,
                                &loudSpeakerBitmap.bitmap };
    Vector2f positions[6] = { Vector2f(0.0f, 0.0f), Vector2f((window->getSize().x) / 2.40f, (window->getSize().y) / 3.20f),
                               Vector2f((window->getSize().x) / 2.40f, (window->getSize().y) / 2.50f), 
                                Vector2f((window->getSize().x) / 2.65f, (window->getSize().y) / 2.05f),
                                Vector2f((window->getSize().x) / 2.6f, (window->getSize().y) / 1.75f),
                                Vector2f((window->getSize().x) / 1.05f, 20.0f) };
    Vector2f scales[6] = { Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(0.2f, 0.2f) };
    SpriteObject gameBackground;
    gameBackground.createSpriteFrom(bitmapArray, 6, positions, scales);
    gameBackground.draw();
}


void Engine::checkArrowRectActions() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect arrowRect(Vector2f((window->getSize().x) / 1.075f, 20.0f), Vector2f(60.0f, 55.0f));
    if (arrowRect.contains(mouseX, mouseY) && Mouse::isButtonPressed(Mouse::Left)) {
        winnerScreenMusic.stop();
        getInstance().activeWindowName = MENU;
        centered = false;
        return;
    }
}

/**
 * @brief Funkcja sprawdza i obsługuje interakcje myszy w menu.
 *
 * Ta funkcja sprawdza pozycję myszy i aktualizuje kolory tekstu
 * na podstawie położenia względem prostokątów menu. Obsługuje również interakcje przycisków.
 */
void Engine::checkMenuRectsActions() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect startRect(Vector2f((window->getSize().x) / 2.40f, (window->getSize().y) / 3.20f), Vector2f(220.0f, 60.0f));
    FloatRect optionsRect(Vector2f((window->getSize().x) / 2.40f, (window->getSize().y) / 2.5f), Vector2f(220.0f, 60.0f));
    FloatRect authorRect(Vector2f((window->getSize().x) / 2.65f, (window->getSize().y) / 2.05f), Vector2f(350.0f, 60.0f));
    FloatRect exitRect(Vector2f((window->getSize().x) / 2.6f, (window->getSize().y) / 1.75f), Vector2f(350.0f, 60.0f));

    if (!startRect.contains(mouseX, mouseY) && !optionsRect.contains(mouseX, mouseY) && !authorRect.contains(mouseX,mouseY) 
        && !exitRect.contains(mouseX,mouseY)){
        startTextColor = Color::White;
        optionsTextColor = Color::White;
    }
    else if (startRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            getInstance().activeWindowName = GAME;
            centered = false;
            return;
        }
        else if (!Mouse::isButtonPressed(Mouse::Left)) {
            startTextColor = Color::Black;
            exitTextColor = Color::White;
            optionsTextColor = Color::White; 
            authorTextColor = Color::White;
        }
    }
    else if (optionsRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            getInstance().activeWindowName = GAME_OPTIONS;
            centered = false;
            return;
        }
        else {
            startTextColor = Color::White;
            authorTextColor = Color::White;
            exitTextColor = Color::White;
            optionsTextColor = Color::Black;
        }
    }
    else if (authorRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            getInstance().activeWindowName = AUTHORS;
            centered = false;
            return;
        }
        else {
            startTextColor = Color::White; 
            optionsTextColor = Color::White;
            exitTextColor = Color::White; 
            authorTextColor = Color::Black;
        }
    }
    else if (exitRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left))
            window->close();
        else {
            startTextColor = Color::White; 
            optionsTextColor = Color::White;
            authorTextColor = Color::White;
            exitTextColor = Color::Black;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Engine::checkGameOptionsRectsActions() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect player1HallandRect(Vector2f((window->getSize().x) / 6.0f, 90.0f), Vector2f(200.0f, 60.0f));
    FloatRect player1MbappeRect(Vector2f((window->getSize().x) / 2.9f, 90.0f), Vector2f(200.0f, 60.0f));
    FloatRect player1MessiRect(Vector2f((window->getSize().x) / 1.9f, 90.0f), Vector2f(120.0f, 60.0f));
    FloatRect player1RonaldoRect(Vector2f((window->getSize().x) / 1.5f, 90.0f), Vector2f(200.0f, 60.0f));

    FloatRect player2HallandRect(Vector2f((window->getSize().x) / 6.0f, 230.0f), Vector2f(200.0f, 60.0f));
    FloatRect player2MbappeRect(Vector2f((window->getSize().x) / 2.9f, 230.0f), Vector2f(200.0f, 60.0f));
    FloatRect player2MessiRect(Vector2f((window->getSize().x) / 1.9f, 230.0f), Vector2f(120.0f, 60.0f));
    FloatRect player2RonaldoRect(Vector2f((window->getSize().x) / 1.5f, 230.0f), Vector2f(200.0f, 60.0f));
    
    FloatRect stadion1Rect(Vector2f((window->getSize().x) / 5.9f, 370.0f), Vector2f(250.0f, 60.0f));
    FloatRect stadion2Rect(Vector2f((window->getSize().x) / 2.4f, 370.0f), Vector2f(250.0f, 60.0f));
    FloatRect stadion3Rect(Vector2f((window->getSize().x) / 1.5f, 370.0f), Vector2f(250.0f, 60.0f));

    FloatRect timer1MinRect(Vector2f((window->getSize().x) / 5.5f, 510.0f), Vector2f(170.0f, 60.0f));
    FloatRect timer3MinRect(Vector2f((window->getSize().x) / 2.85f, 510.0f), Vector2f(170.0f, 60.0f));
    FloatRect timer5MinRect(Vector2f((window->getSize().x) / 1.9f, 510.0f), Vector2f(170.0f, 60.0f));
    FloatRect timer10MinRect(Vector2f((window->getSize().x) / 1.45f, 510.0f), Vector2f(170.0f, 60.0f));

    FloatRect limit1GoalRect(Vector2f((window->getSize().x) / 5.5f, 640.0f), Vector2f(170.0f, 60.0f));
    FloatRect limit3GoalRect(Vector2f((window->getSize().x) / 2.85f, 640.0f), Vector2f(170.0f, 60.0f));
    FloatRect limit5GoalRect(Vector2f((window->getSize().x) / 1.9f, 640.0f), Vector2f(170.0f, 60.0f));
    FloatRect limit10GoalRect(Vector2f((window->getSize().x) / 1.45f, 640.0f), Vector2f(170.0f, 60.0f));

    
    //Wybor skina playera 1
    if (player1HallandRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player1HallandTextColor = Color::Red;
            player1MbappeTextColor = Color::White;
            player1MessiTextColor = Color::White;
            player1RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin1";
        }
    }
    else if (player1MbappeRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player1HallandTextColor = Color::White;
            player1MbappeTextColor = Color::Red;
            player1MessiTextColor = Color::White;
            player1RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin2";
        }
    }
    else if (player1MessiRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player1HallandTextColor = Color::White;
            player1MbappeTextColor = Color::White;
            player1MessiTextColor = Color::Red;
            player1RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin3";
        }
    }
    else if (player1RonaldoRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player1HallandTextColor = Color::White;
            player1MbappeTextColor = Color::White;
            player1MessiTextColor = Color::White;
            player1RonaldoTextColor = Color::Red;
            //leftPlayerSkin = "skin4";
        }
    }
    else {
        //player1HallandTextColor = Color::White;
        //player1MbappeTextColor = Color::White;
        //player1MessiTextColor = Color::White;
        //player1RonaldoTextColor = Color::White;
    }

    //Wybor skina playera 2
    if (player2HallandRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player2HallandTextColor = Color::Red;
            player2MbappeTextColor = Color::White;
            player2MessiTextColor = Color::White;
            player2RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin1";
        }
    }
    else if (player2MbappeRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player2HallandTextColor = Color::White;
            player2MbappeTextColor = Color::Red;
            player2MessiTextColor = Color::White;
            player2RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin2";
        }
    }
    else if (player2MessiRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player2HallandTextColor = Color::White;
            player2MbappeTextColor = Color::White;
            player2MessiTextColor = Color::Red;
            player2RonaldoTextColor = Color::White;
            //leftPlayerSkin = "skin3";
        }
    }
    else if (player2RonaldoRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            player2HallandTextColor = Color::White;
            player2MbappeTextColor = Color::White;
            player2MessiTextColor = Color::White;
            player2RonaldoTextColor = Color::Red;
            //leftPlayerSkin = "skin4";
        }
    }
    else {
        //player2HallandTextColor = Color::White;
        //player2MbappeTextColor = Color::White;
        //player2MessiTextColor = Color::White;
        //player2RonaldoTextColor = Color::White;
    }

    //Wybor stadionu
    if (stadion1Rect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            stadion1TextColor = Color::Red;
            stadion2TextColor = Color::White;
            stadion3TextColor = Color::White;
            stadiumSkin = "stadium1";
        }
    }
    else if (stadion2Rect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            stadion1TextColor = Color::White;
            stadion2TextColor = Color::Red;
            stadion3TextColor = Color::White;
            stadiumSkin = "stadium2";
        }
    }
    else if (stadion3Rect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            stadion1TextColor = Color::White;
            stadion2TextColor = Color::White;
            stadion3TextColor = Color::Red;
            stadiumSkin = "stadium3";
        }
    }
    else {
        //stadion1TextColor = Color::White;
        //stadion2TextColor = Color::White;
        //stadion3TextColor = Color::White;
    }

    //wybor timera meczu
    if (timer1MinRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            timer1TextColor = Color::Red;
            timer3TextColor = Color::White;
            timer5TextColor = Color::White;
            timer10TextColor = Color::White;
            secondsRequiredToEndTheGame = 60;
        }
    }
    else if (timer3MinRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            timer1TextColor = Color::White;
            timer3TextColor = Color::Red;
            timer5TextColor = Color::White;
            timer10TextColor = Color::White;
            secondsRequiredToEndTheGame = 180;
        }
    }
    else if (timer5MinRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            timer1TextColor = Color::White;
            timer3TextColor = Color::White;
            timer5TextColor = Color::Red;
            timer10TextColor = Color::White;
            secondsRequiredToEndTheGame = 300;
        }
    }
    else if (timer10MinRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            timer1TextColor = Color::White;
            timer3TextColor = Color::White;
            timer5TextColor = Color::White;
            timer10TextColor = Color::Red;
            secondsRequiredToEndTheGame = 600;
        }
    }
    else {
        //timer1TextColor = Color::White;
        //timer3TextColor = Color::White;
        //timer5TextColor = Color::White;
        //timer10TextColor = Color::White;
    }

    //wybor goli meczu
    if (limit1GoalRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            limit1GoalTextColor = Color::Red;
            limit3GoalTextColor = Color::White;
            limit5GoalTextColor = Color::White;
            limit10GoalTextColor = Color::White;
            goalCountRequiredToWin = 1;
        }
    }
    else if (limit3GoalRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            limit1GoalTextColor = Color::White;
            limit3GoalTextColor = Color::Red;
            limit5GoalTextColor = Color::White;
            limit10GoalTextColor = Color::White;
            goalCountRequiredToWin = 3;
        }
    }
    else if (limit5GoalRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            limit1GoalTextColor = Color::White;
            limit3GoalTextColor = Color::White;
            limit5GoalTextColor = Color::Red;
            limit10GoalTextColor = Color::White;
            goalCountRequiredToWin = 5;
        }
    }
    else if (limit10GoalRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Wybrano opcje 
            limit1GoalTextColor = Color::White;
            limit3GoalTextColor = Color::White;
            limit5GoalTextColor = Color::White;
            limit10GoalTextColor = Color::Red;
            goalCountRequiredToWin = 10;
        }
    }
    else {
        //limit1GoalTextColor = Color::White;
        //limit3GoalTextColor = Color::White;
        //limit5GoalTextColor = Color::White;
        //limit10GoalTextColor = Color::White;
    }








}













bool Engine::checkIsGoalAtLeftGate() {
    FloatRect leftGateGoalRect(0.0f, (window->getSize().y) / 3.25f, (window->getSize().x) / 10.0f, (window->getSize().y) / 2.3f);
    Vector2f ballPosition(ball.getActualPosition().x, ball.getActualPosition().y);
    if (leftGateGoalRect.contains(ballPosition)) {
        pause = true;
        music.stop();
        if (!mute) {
            goalMusic.openFromFile("sounds/goalYmbape.wav");
            goalMusic.play();
        }
        return true;
    }
    return false;
}

bool Engine::checkIsGoalAtRightGate() {
    FloatRect rightGateGoalRect((window->getSize().x) / 1.175f, (window->getSize().y) / 3.2f, 
        (window->getSize().x) / 10.0f, (window->getSize().y) / 2.5f);
    Vector2f ballPosition(ball.getActualPosition().x, ball.getActualPosition().y);
    if (rightGateGoalRect.contains(ballPosition)) {
        pause = true;
        music.stop();
        if (!mute) {
            goalMusic.openFromFile("sounds/goalHaaland.wav");
            goalMusic.play();
        }
        return true;
    }
    return false;
}

/**
 * @brief Funkcja ustawia tło gry i wszystkie elementy gry.
 *
 * Ta funkcja konfiguruje tło gry poprzez tworzenie ikonek dla różnych
 * elementy takie jak bramki, teksty i gracze. Zajmuje się także pozycjonowaniem
 * i skalowanie tych elementów na ekranie.
 *
 * @param currentTime Bieżący czas.
 */
void Engine::setGameBackground(string currentTime) {
    float elapsedIceEffectTime = iceEffectRespawnTimer.getElapsedTime().asSeconds();
    float elapsedBrokenLegEffectTime = brokenLegEffectRespawnTimer.getElapsedTime().asSeconds();
    float elapsedExistingEffectTime = effectExistingTimer.getElapsedTime().asSeconds();
    float elapsedSeconds = totalElapsedTime;
    cout << elapsedExistingEffectTime << endl;
    if (!pause) 
        elapsedSeconds = gameTimer.getElapsedTime().asSeconds() + totalElapsedTime;
    checkRectsActions();
    moveBall();
    int differenceInSeconds = static_cast<int>(secondsRequiredToEndTheGame - elapsedSeconds);
    int minutes = differenceInSeconds / 60;
    int seconds = differenceInSeconds % 60;
    string timeString = to_string(minutes) + ":";
    if (seconds >= 10)
        timeString += to_string(seconds);
    else if (seconds < 10)
        timeString += "0" + to_string(seconds);
    BitmapHandler leftGateBitmap("elements/game/BramkaL.png");
    BitmapHandler rightGateBitmap("elements/game/BramkaP.png");
    BitmapHandler fpsTextBitmap(getText(Color::White, currentTime), Vector2i(100, 100), Color::Transparent);
    BitmapHandler pauseTextBitmap(getText(pauseTextColor, 42, "PAUZA"), Vector2i(200, 200), Color::Transparent);
    BitmapHandler menuTextBitmap(getText(menuTextColor, 42, "MENU"), Vector2i(150, 150), Color::Transparent);
    BitmapHandler leftPlayerPointsTextBitmap(getText(Color::Black, 42, to_string(leftPlayerPoints)), Vector2i(50, 50), 
                                               Color::Transparent);
    BitmapHandler rightPlayerPointsTextBitmap(getText(Color::Black, 42, to_string(rightPlayerPoints)), 
                                                Vector2i(50, 50), Color::Transparent);
    BitmapHandler timeLeftBitmap(getText(Color::Green, 42, timeString), Vector2i(150, 100), Color::Transparent);
    BitmapHandler leftPlayerBitmap = leftPlayer.getPlayerBitmap();
    BitmapHandler rightPlayerBitmap = rightPlayer.getPlayerBitmap();
    BitmapHandler ballBitmap = ball.getBallBitmap();
    SpriteObject gameBackground;
    if (elapsedIceEffectTime >= 60) {
       Texture* bitmapArray[8] = { &backgroundTexture.bitmap, &fpsTextBitmap.bitmap, &pauseTextBitmap.bitmap,
       &menuTextBitmap.bitmap, &leftPlayerPointsTextBitmap.bitmap, &rightPlayerPointsTextBitmap.bitmap,
       &timeLeftBitmap.bitmap, &iceCubeBitmap.bitmap };
        Vector2f positions[8] = { Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f),
            Vector2f((window->getSize().x) / 2.22f, (window->getSize().y) / 1.22f),
            Vector2f((window->getSize().x) / 2.17f, (window->getSize().y) / 1.13f),
            Vector2f((window->getSize().x) / 2.5f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 1.715f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 2.1f, (window->getSize().y) / 12.0f),
            Vector2f(0.0f, 0.0f)};
        Vector2f scales[8] = { Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),
                                Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(0.05f, 0.05f) };
        gameBackground.createSpriteFrom(bitmapArray, 8, positions, scales);
    }
    else if (elapsedBrokenLegEffectTime >= 60) {
        Texture* bitmapArray[8] = { &backgroundTexture.bitmap, &fpsTextBitmap.bitmap, &pauseTextBitmap.bitmap,
        &menuTextBitmap.bitmap, &leftPlayerPointsTextBitmap.bitmap, &rightPlayerPointsTextBitmap.bitmap,
        &timeLeftBitmap.bitmap, &leftBrokenLegBitmap.bitmap };
        Vector2f positions[8] = { Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f),
            Vector2f((window->getSize().x) / 2.22f, (window->getSize().y) / 1.22f),
            Vector2f((window->getSize().x) / 2.17f, (window->getSize().y) / 1.13f),
            Vector2f((window->getSize().x) / 2.5f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 1.715f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 2.1f, (window->getSize().y) / 12.0f),
            Vector2f(0.0f, 0.0f) };
        Vector2f scales[8] = { Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),
                                Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(0.5f, 0.5f)};
        gameBackground.createSpriteFrom(bitmapArray, 8, positions, scales);
    }
    else if(elapsedExistingEffectTime >= 90 || elapsedIceEffectTime <= 60 || elapsedBrokenLegEffectTime <= 60 ){
        Texture* bitmapArray[7] = { &backgroundTexture.bitmap, &fpsTextBitmap.bitmap, &pauseTextBitmap.bitmap,
        &menuTextBitmap.bitmap, &leftPlayerPointsTextBitmap.bitmap, &rightPlayerPointsTextBitmap.bitmap,
        &timeLeftBitmap.bitmap };
        Vector2f positions[7] = { Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f),
            Vector2f((window->getSize().x) / 2.22f, (window->getSize().y) / 1.22f),
            Vector2f((window->getSize().x) / 2.17f, (window->getSize().y) / 1.13f),
            Vector2f((window->getSize().x) / 2.5f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 1.715f , (window->getSize().y) / 12.0f),
            Vector2f((window->getSize().x) / 2.1f, (window->getSize().y) / 12.0f) };
        Vector2f scales[7] = { Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f),
                                Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f) };
        gameBackground.createSpriteFrom(bitmapArray, 7, positions, scales);
        if (elapsedExistingEffectTime >= 90) {
            brokenLegEffectRespawnTimer.restart();
            iceEffectRespawnTimer.restart();
            effectExistingTimer.restart();
        }
    }
    SpriteObject leftPlayerSprite(&(leftPlayerBitmap.bitmap), leftPlayer.getActualPosition(), Vector2f(0.1f, 0.1f));
    SpriteObject rightPlayerSprite(&(rightPlayerBitmap.bitmap), rightPlayer.getActualPosition(), Vector2f(0.1f, 0.1f));
    SpriteObject ballSprite(&(ballBitmap.bitmap), ball.getActualPosition(), Vector2f(0.05f, 0.05f));
    SpriteObject leftGateSprite(&(leftGateBitmap.bitmap), getGatePosition("left"), Vector2f(1.0f, 1.0f));
    SpriteObject rightGateSprite(&(rightGateBitmap.bitmap), getGatePosition("right"), Vector2f(1.0f, 1.0f));
    checkPlayerActions(leftPlayerSprite, rightPlayerSprite);
    checkCollisions();
    gameBackground.draw();
    if (leftPlayerPoints > goalCountRequiredToWin || rightPlayerPoints > goalCountRequiredToWin ||
        elapsedSeconds >= secondsRequiredToEndTheGame) {
        if (leftPlayerPoints > rightPlayerPoints)
            winnerNumber = 1;
        else if (leftPlayerPoints < rightPlayerPoints)
            winnerNumber = 2;
        leftPlayerPoints = 0;
        rightPlayerPoints = 0;
        endedGame = true;
        centered = false;
        finalWhistleMusic.openFromFile("sounds/final_whistle.wav");
        finalWhistleMusic.play();
        gameTimer.restart();
        whistleMusic.stop();
        goalMusic.stop();
        music.stop();
        sleep(sf::seconds(2));
        getInstance().activeWindowName = WINNER_SCREEN;
        return;
    }
}

/**
 * @brief Funkcja sprawdza i obsługuje akcje w oparciu o pozycję myszy i kliknięcia przycisków w grze.
 *
 * Ta funkcja sprawdza pozycję myszy i wykonuje odpowiednie działania,
 * takie jak zmiana kolorów tekstu i obsługa kliknięć przycisków.
 */
void Engine::checkRectsActions() {
    Vector2i mouseBounds = Mouse::getPosition(*window);
    float mouseX = mouseBounds.x;
    float mouseY = mouseBounds.y;
    FloatRect pauseRect(Vector2f((window->getSize().x) / 2.22f, (window->getSize().y) / 1.22f), Vector2f(150.0f, 40.0f));
    FloatRect menuRect(Vector2f((window->getSize().x) / 2.22f, (window->getSize().y) / 1.12f), Vector2f(150.0f, 40.0f));
    if (!pauseRect.contains(mouseX, mouseY) && !menuRect.contains(mouseX, mouseY) && !pause) {
        pauseTextColor = Color::White;
        menuTextColor = Color::White;
    }
    else if (pauseRect.contains(mouseX, mouseY)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (!pause) {
                pause = true;
                music.pause();
                pauseTextColor = Color::Black;
                ball.setActualSpeed(0.0f);
                sleep(seconds(0.25f));
                totalElapsedTime += gameTimer.getElapsedTime().asSeconds();
            }
            else if (pause) {
                pause = false;
                if(!mute)
                    music.play();
                pauseTextColor = Color::White;
                ball.setActualSpeed(7.5f);
                sleep(seconds(0.25f));
                gameTimer.restart();
            }
        }
        else if (!Mouse::isButtonPressed(Mouse::Left) && !pause) {
            pauseTextColor = Color::Black;
            menuTextColor = Color::White;
        }
    }
    else if (menuRect.contains(mouseX, mouseY) && !pause) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            gameTimer.restart();
            leftPlayerPoints = 0;
            rightPlayerPoints = 0;
            getInstance().activeWindowName = MENU;
            centered = false;
            music.stop();
            goalMusic.stop();
            whistleMusic.stop();
            finalWhistleMusic.stop();
            return;
        }
        else {
            pauseTextColor = Color::White;
            menuTextColor = Color::Black;
        }
    }
}

void Engine::moveBall() {
    if (!pause) {
        Vector2f ballPosition = ball.getActualPosition();
        random_device rd;
        default_random_engine engine(rd());
        uniform_real_distribution<float> distribution(0.5f, 1.0f);
        float randomFloat = distribution(engine);
        FloatRect bottomCollisionRect(0.0f, (window->getSize().y) / 1.45f, window->getSize().x, (window->getSize().y) / 2.0f);
        switch (ballMoveDirection) {
            case NORTH:
                ball.setActualPosition(Vector2f(ballPosition.x, ballPosition.y - ball.getActualSpeed()));
            break;
            case SOUTH:
                ball.setActualPosition(Vector2f(ballPosition.x, ballPosition.y + ball.getActualSpeed()));
            break;
            case WEST:
                ball.setActualPosition(Vector2f(ballPosition.x - ball.getActualSpeed() * randomFloat,
                    ballPosition.y));
            break;
            case EAST:
                ball.setActualPosition(Vector2f(ballPosition.x + ball.getActualSpeed() * randomFloat,
                    ballPosition.y));
            break;
            case NORTH_EAST:
                ball.setActualPosition(Vector2f(ballPosition.x + ball.getActualSpeed() * randomFloat,
                    ballPosition.y - ball.getActualSpeed() / 1.05f));
            break;
            case SOUTH_EAST:
                if (!bottomCollisionRect.contains(ballPosition))
                    ball.setActualPosition(Vector2f(ballPosition.x + ball.getActualSpeed() * randomFloat,
                        ballPosition.y + ball.getActualSpeed()));
                else
                    ball.setActualPosition(Vector2f(ballPosition.x + ball.getActualSpeed() * randomFloat,
                        ballPosition.y));
            break;
            case NORTH_WEST:
                ball.setActualPosition(Vector2f(ballPosition.x - ball.getActualSpeed() * randomFloat,
                    ballPosition.y - ball.getActualSpeed() / 1.05f));
            break;
            case SOUTH_WEST:
                if (!bottomCollisionRect.contains(ballPosition))
                    ball.setActualPosition(Vector2f(ballPosition.x - ball.getActualSpeed() * randomFloat,
                        ballPosition.y + ball.getActualSpeed()));
                else
                    ball.setActualPosition(Vector2f(ballPosition.x - ball.getActualSpeed() * randomFloat,
                        ballPosition.y));
            break;
        }
    }
}

/**
 * @brief Funkcja sprawdza działania graczy i aktualizuje ich pozycje oraz animacje.
 *
 * Ta funkcja sprawdza wprowadzane dane z klawiatury w celu kontrolowania ruchu i animacji
 * dwóch graczy. Pobiera dwa parametry SpriteObject reprezentujące graczy.
 *
 * @param player1 Obiekt SpriteObject dla pierwszego gracza.
 * @param player2 Obiekt SpriteObject dla drugiego gracza.
 */
void Engine::checkPlayerActions(SpriteObject player1, SpriteObject player2) {
    Sprite player1Sprite = player1.getSprite();
    Sprite player2Sprite = player2.getSprite();
    Vector2f leftPlayerPosition(leftPlayer.getActualPosition().x, leftPlayer.getActualPosition().y);
    Vector2f rightPlayerPosition(rightPlayer.getActualPosition().x, rightPlayer.getActualPosition().y);
    FloatRect leftCollisionRect(0.0f, 0.0f, (window->getSize().x) / 10.0f, window->getSize().y);
    FloatRect rightCollisionRect((window->getSize().x) / 1.3f, 0.0f, (window->getSize().x) / 1.3f, window->getSize().y);
    if (!pause) {
        if (Keyboard::isKeyPressed(Keyboard::W)) 
            leftPlayer.setActualPosition(Vector2f(leftPlayer.getActualPosition().x, 
                getPlayerPosition("Haaland").y - leftPlayer.getActualSpeed() * 15.0f), "left");
        else if (!Keyboard::isKeyPressed(Keyboard::W) && leftPlayer.getActualPosition().y!= getPlayerPosition("Haaland").y)
            leftPlayer.setActualPosition(Vector2f(leftPlayer.getActualPosition().x, getPlayerPosition("Haaland").y), "left");
        else if (Keyboard::isKeyPressed(Keyboard::A) && !leftCollisionRect.contains(leftPlayerPosition)) {
            player1Sprite.move(Vector2f(-leftPlayer.getActualSpeed(), 0.0f));
            if (!Keyboard::isKeyPressed(Keyboard::W))
                leftPlayer.setActualPosition(player1Sprite.getPosition(), "left");
        }
        else if (Keyboard::isKeyPressed(Keyboard::D) && (leftPlayerPosition.x + 100.0f < rightPlayerPosition.x)
            && !rightCollisionRect.contains(leftPlayerPosition)) {
            player1Sprite.move(Vector2f(leftPlayer.getActualSpeed(), 0.0f));
            if (!Keyboard::isKeyPressed(Keyboard::W))
                leftPlayer.setActualPosition(player1Sprite.getPosition(), "left");
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
            rightPlayer.setActualPosition(Vector2f(rightPlayer.getActualPosition().x, 
                getPlayerPosition("Ymbape").y - rightPlayer.getActualSpeed() * 15.0f), "right");
        else if (!Keyboard::isKeyPressed(Keyboard::Up) && rightPlayer.getActualPosition().y != getPlayerPosition("Ymbape").y)
            rightPlayer.setActualPosition(Vector2f(rightPlayer.getActualPosition().x, getPlayerPosition("Ymbape").y), "right");
        else if (Keyboard::isKeyPressed(Keyboard::Left) && (leftPlayerPosition.x < rightPlayerPosition.x - 100.0f) &&
            !leftCollisionRect.contains(rightPlayerPosition)) {
            player2Sprite.move(Vector2f(-rightPlayer.getActualSpeed(), 0.0f));
            if (!Keyboard::isKeyPressed(Keyboard::Up))
                rightPlayer.setActualPosition(player2Sprite.getPosition(), "right");
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && !rightCollisionRect.contains(rightPlayerPosition)) {
            player2Sprite.move(Vector2f(rightPlayer.getActualSpeed(), 0.0f));
            if (!Keyboard::isKeyPressed(Keyboard::Up))
                rightPlayer.setActualPosition(player2Sprite.getPosition(), "right");
        }
        if (Keyboard::isKeyPressed(Keyboard::X)) {
            player1.animate(leftPlayerShot, &leftPlayer);
            leftPlayer.isShooting = true;
        }
        else {
            player1.animate(leftPlayerBitmap, &leftPlayer);
            leftPlayer.isShooting = false;
        }
        if(Keyboard::isKeyPressed(Keyboard::M)) {
            player2.animate(rightPlayerShot, &rightPlayer);
            rightPlayer.isShooting = true;
        }
        else {
            player2.animate(rightPlayerBitmap, &rightPlayer);
            rightPlayer.isShooting = false;
        }
    }
}

/**
 * @brief Funkcja sprawdza kolizje w silniku gry.
 *
 * Ta funkcja sprawdza kolizje w różnych obszarach okna gry.
 * Prostokąty kolizyjne obejmują dolną, górną, lewą i prawą granicę,
 * jak również określone obszary bramek dla lewej i prawej bramki.
 */
void Engine::checkCollisions() {
    if (!pause) {
        srand(time(NULL));
        FloatRect bottomCollisionRect(0.0f, (window->getSize().y) / 1.45f, window->getSize().x, (window->getSize().y) / 2.0f);
        FloatRect topCollisionRect(0.0f, 0.0f, window->getSize().x, (window->getSize().y) / 5.0f);
        FloatRect leftCollisionRect(0.0f, 0.0f, (window->getSize().x) / 10.0f, window->getSize().y);
        FloatRect rightCollisionRect((window->getSize().x) / 1.1f, 0.0f, (window->getSize().x) / 1.3f, window->getSize().y);
        FloatRect leftGateGoalRect(0.0f, (window->getSize().y) / 3.25f, (window->getSize().x) / 10.0f, (window->getSize().y) / 2.3f);
        FloatRect rightGateGoalRect((window->getSize().x) / 1.175f, (window->getSize().y) / 3.2f, 
            (window->getSize().x) / 6.0f, (window->getSize().y) / 2.5f);
        Vector2f ballPosition(ball.getActualPosition().x, ball.getActualPosition().y);
        Vector2f leftPlayerPosition(leftPlayer.getActualPosition().x, leftPlayer.getActualPosition().y);
        Vector2f rightPlayerPosition(rightPlayer.getActualPosition().x, rightPlayer.getActualPosition().y);
        if (!checkIsGoalAtLeftGate() && !checkIsGoalAtRightGate() && !checkIsCollisionWithPlayer()) {
            if (leftCollisionRect.contains(ballPosition) && !leftGateGoalRect.contains(ballPosition)
                && !topCollisionRect.contains(ballPosition) && !bottomCollisionRect.contains(ballPosition))
                ballMoveDirection = NORTH_EAST;
            else if (rightCollisionRect.contains(ballPosition) && !rightGateGoalRect.contains(ballPosition)
                && !topCollisionRect.contains(ballPosition) && !bottomCollisionRect.contains(ballPosition))
                ballMoveDirection = NORTH_WEST;
            else if (topCollisionRect.contains(ballPosition) && !rightCollisionRect.contains(ballPosition)
                && !leftCollisionRect.contains(ballPosition) && !bottomCollisionRect.contains(ballPosition)
                && ballMoveDirection != SOUTH)
                ballMoveDirection = SOUTH;
            else if (bottomCollisionRect.contains(ballPosition) && !rightCollisionRect.contains(ballPosition)
                && !leftCollisionRect.contains(ballPosition) && !topCollisionRect.contains(ballPosition)) {
                ballMoveDirection = 2 + rand() % 2;
                ball.setActualSpeed(ball.getActualSpeed() / 1.025f);
            }
            else if (leftCollisionRect.contains(ballPosition) && (ballMoveDirection == WEST
                || ballMoveDirection == NORTH_WEST || ballMoveDirection == SOUTH_WEST))
                ballMoveDirection = EAST;
            else if (rightCollisionRect.contains(ballPosition) && !rightGateGoalRect.contains(ballPosition)
                && !topCollisionRect.contains(ballPosition)
                && ballMoveDirection != WEST)
                ballMoveDirection = WEST;
        }
        bool goalLeft = checkIsGoalAtLeftGate();
        bool goalRight = checkIsGoalAtRightGate();
        if (goalLeft || goalRight) {
            if (goalLeft)
                rightPlayerPoints++;
            else
                leftPlayerPoints++;
            while (goalTimer.getElapsedTime().asSeconds() < 3);
            centered = false;
            pause = false;
            goalTimer.restart();
        }
    }
}

/**
 * @brief Funkcja obsługuje zdarzenie zamknięcia okna, sprawdzając i odpowiadając na różne typy zdarzeń.
 *
 * Ta funkcja sprawdza różne typy zdarzeń za pomocą pętli i podejmuje odpowiednie działania w zależności od typu zdarzenia.
 *
 */
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

bool Engine::checkIsCollisionWithPlayer() {
    bool isCollision = false;
    if (!pause) {
        Vector2f ballPosition = ball.getActualPosition();
        FloatRect bottomCollisionRect(0.0f, (window->getSize().y) / 1.45f, window->getSize().x, (window->getSize().y) / 2.0f);
        if (leftPlayer.shoeRect.contains(ballPosition) && leftPlayer.isShooting) {
            ballMoveDirection = NORTH_EAST;
            ball.setActualSpeed(10.5f);
            isCollision = true;
        }
        if (rightPlayer.shoeRect.contains(ballPosition) && rightPlayer.isShooting) {
            ballMoveDirection = NORTH_WEST;
            ball.setActualSpeed(10.5f);
            isCollision = true;
        }
        else if (leftPlayer.topRect.contains(ballPosition)) {
            ballMoveDirection = NORTH_EAST;
            isCollision = true;
        }
        else if (rightPlayer.topRect.contains(ballPosition)) {
            ballMoveDirection = NORTH_WEST;
            isCollision = true;
        }
        else if (leftPlayer.leftRect.contains(ballPosition) || rightPlayer.rightRect.contains(ballPosition)
            && !bottomCollisionRect.contains(ballPosition)) {
            ballMoveDirection = SOUTH_EAST;
            isCollision = true;
        }
        else if (leftPlayer.rightRect.contains(ballPosition) || rightPlayer.leftRect.contains(ballPosition)
            && !bottomCollisionRect.contains(ballPosition)) {
            ballMoveDirection = SOUTH_WEST;
            isCollision = true;
        }
        else if (leftPlayer.leftRect.contains(ballPosition) || rightPlayer.rightRect.contains(ballPosition)
            && bottomCollisionRect.contains(ballPosition)) {
            ballMoveDirection = NORTH_EAST;
            isCollision = true;
        }
        else if (leftPlayer.rightRect.contains(ballPosition) || rightPlayer.leftRect.contains(ballPosition)
            && bottomCollisionRect.contains(ballPosition)) {
            ballMoveDirection = NORTH_WEST;
            isCollision = true;
        }
    }
    return isCollision;
}

/**
 * @brief Funkcja rysuje przyciski na ekranie ustawień, w tym przyciski wyboru rozdzielczości i przycisk graj.
 *
 * Ta funkcja rysuje przyciski na ekranie w oparciu o bieżący stan, np. wybraną rozdzielczość
 * przyciski i przycisk odtwarzania. Obsługuje również interakcje przycisków i odpowiednio aktualizuje kolory przycisków.
 */
void Engine::drawButtons() {
    Rectangle playButton = getButton(260, Color::Red, Vector2f(200, 50));
    int rectName = getRectNameWhenMouseIsPressedIn();
    switch (rectName) {
        case RESOLUTION_1:
            resolution1Button = getButton(20, Color::Red, Vector2f(200, 50));
            resolution2Button = getButton(100, Color::Green, Vector2f(200, 50));
            resolution3Button = getButton(180, Color::Green, Vector2f(200, 50));
        break;
        case RESOLUTION_2:
            resolution1Button = getButton(20, Color::Green, Vector2f(200, 50));
            resolution2Button = getButton(100, Color::Red, Vector2f(200, 50));
            resolution3Button = getButton(180, Color::Green, Vector2f(200, 50));
        break;
        case RESOLUTION_3:
            resolution1Button = getButton(20, Color::Green, Vector2f(200, 50));
            resolution2Button = getButton(100, Color::Green, Vector2f(200, 50));
            resolution3Button = getButton(180, Color::Red, Vector2f(200, 50));
        break;
        case PLAY:
            setWidthAndHeight(resolution1Button, resolution2Button, resolution3Button);
        break;
    }
    resolution1Button.draw();
    resolution2Button.draw();
    resolution3Button.draw();
    playButton.draw();
}

/**
 * @brief Funkcja rysuje teksty w oknie ustawień.
 *
 * Ta funkcja tworzy obiekty tekstowe o określonej treści (tytuły rozdzielczości) i kolorze, ustala ich położenie,
 * a następnie rysuje je na oknie ustawień.
 */
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

/**
 * @brief Funkcja obsługuje wymianę i aktualizację podwójnych buforów do renderowania.
 *
 * Ta funkcja ustawia limit liczby klatek na sekundę i przełącza pomiędzy dwoma buforami (głównym i drugim)
 * dla płynniejszego renderowania. Czyści nieaktywny bufor, ustawia zawartość aktywnego bufora
 * na nieaktywny, a następnie wyświetla zaktualizowaną zawartość w oknie.
 *
 * Jeśli aktywny bufor jest „główny”, czyści drugi bufor i rysuje teksturę głównego bufora
 * i wyświetla drugi bufor w oknie. Aktywny bufor jest wówczas ustawiany na „drugi”.
 *
 * Jeśli aktywny bufor jest „drugi”, czyści bufor główny, rysuje teksturę drugiego bufora
 * główny bufor i wyświetla główny bufor w oknie. Aktywny bufor jest wówczas ustawiany na „główny”.
 */
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
}

/**
 * @brief Funkcja czyści okno do określonego koloru.
 *
 * Ta funkcja czyści powiązane okno do określonego koloru.
 *
 * @param color Kolor, do którego okno zostanie wyczyszczone.
 */
void Engine::clearWindowToColor(Color color) {
    window->clear(color);
}

/**
 * @brief Funkcja czyści danego Sprita poprzez ustawienie jego koloru.
 *
 * Ta funkcja ustawia kolor dostarczonego Sprite, skutecznie go usuwając
 * na podany kolor.
 *
 * @param sprite Sprite, który ma zostać wyczyszczony.
 * @param color Kolor, jaki należy ustawić dla Sprite.
 */
void Engine::clearSpriteToColor(Sprite& sprite, Color color) {
    sprite.setColor(color);
}

/**
 * @brief Funkcja sprawdza format zawartości dziennika.
 *
 * Ta funkcja sprawdza, czy zawartość dziennika zawiera prawidłowe znaczniki dziennika, takie jak „[ERROR]”, „[INFO]” lub „[DEBUG]”.
 *
 * @return true, jeśli zawartość dziennika jest prawidłowa, w przeciwnym razie false.
 */
bool Engine::validateLogContentFormat() {
    size_t isValidErrorStart = this->logContent.find("[ERROR]");
    size_t isValidInfoStart = this->logContent.find("[INFO]");
    size_t isValidDebugStart = this->logContent.find("[DEBUG]");
    if (isValidErrorStart != string::npos || isValidInfoStart != string::npos || isValidDebugStart != string::npos)
        return true;
    else
        return false;
}

/**
 * @brief Funkcja zapisuje bieżącą zawartość dziennika do pliku i drukuje ją na konsoli.
 *
 * Ta funkcja otwiera plik o nazwie „logs.log” w trybie dopisywania, zapisuje bieżący
 * log do niego zawartość, a następnie zamyka plik. Dodatkowo drukuje logi i ich
 * zawartość do konsoli.
 *
 * @note Plik „logs.log” zostanie utworzony, jeśli nie istnieje.
 */
void Engine::saveLog() {
    fstream fileStream;
    fileStream.open("logs.log", ios::app);
    fileStream << logContent << endl;
    fileStream.close();
    cout << logContent << endl;
}

/**
 * @file main.cpp
 * @brief Główna funkcja aplikacji.
 */
int main() {
    Engine::getInstance().activeWindowName = STARTUP_SETTINGS;
    Engine::getInstance().mainWindowSetup();
    return 0;
}