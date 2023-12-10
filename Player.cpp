#include "Engine.hpp"

using namespace Game;

/**
 * @brief Ustawia aktualn¹ prêdkoœæ gracza.
 *
 * @param speed Nowa prêdkoœæ gracza.
 */
void Engine::Player::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}

/**
 * @brief Ustawia bitmapê gracza.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj¹cy bitmapê gracza.
 */
void Engine::Player::setPlayerBitmap(BitmapHandler bitmap) {
	this->playerBitmap = bitmap;
}

/**
 * @brief Ustawia aktualn¹ pozycjê gracza.
 *
 * @param position Nowa pozycja gracza.
 */
void Engine::Player::setActualPosition(Vector2f position, string positionSite) {
	Vector2f topPosition(position.x, position.y);
	Vector2f leftPosition(position.x, position.y);
	Vector2f rightPosition(position.x, position.y);
	Vector2f shoePosition(position.x, position.y);
	RectangleShape testRect;
	if (positionSite == "left") {
		topPosition.x += 45.0f;
		leftPosition.x += 50.0f;
		rightPosition.x += 20.0f;
		shoePosition.x += 85.0f;
		shoePosition.y += 120.0f;
	}
	else {
		topPosition.x += 65.0f;
		leftPosition.x += 45.0f;
		rightPosition.x += 150.0f;
		shoePosition.x += 25.0f;
		shoePosition.y += 120.0f;
	}
	FloatRect topRect(topPosition, Vector2f(75.0f, 25.0f));
	FloatRect leftRect(leftPosition, Vector2f((getInstance().window->getSize().x) / 8.5f, 
		(getInstance().window->getSize().y) / 4.0f));
	testRect.setFillColor(Color::Red);
	testRect.setSize(Vector2f(100.0f, 100.0f));
	testRect.setPosition(shoePosition);
	getInstance().backgroundRenderTexture->draw(testRect);
	FloatRect rightRect(rightPosition, Vector2f(30.0f, 140.0f));
	FloatRect shoeRect(shoePosition, Vector2f(100.0f, 100.0f));
	this->position = position;
	this->topRect = topRect;
	this->leftRect = leftRect;
	this->rightRect = rightRect;
	this->shoeRect = shoeRect;
}

/**
 * @brief Pobiera aktualn¹ prêdkoœæ gracza.
 *
 * @return Aktualna prêdkoœæ gracza.
 */
float Engine::Player::getActualSpeed() {
	return this->actualSpeed;
}

/**
 * @brief Pobiera aktualn¹ pozycjê gracza.
 *
 * @return Obiekt Vector2f reprezentuj¹cy aktualn¹ pozycjê gracza.
 */
Vector2f Engine::Player::getActualPosition() {
	return this->position;
}

/**
 * @brief Pobiera bitmapê gracza.
 *
 * @return Obiekt BitmapHandler reprezentuj¹cy bitmapê gracza.
 */
Engine::BitmapHandler Engine::Player::getPlayerBitmap() {
	return this->playerBitmap;
}