#include "Engine.hpp"

using namespace Game;

/**
 * @brief Ustawia aktualn� pr�dko�� gracza.
 *
 * @param speed Nowa pr�dko�� gracza.
 */
void Engine::Player::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}

/**
 * @brief Ustawia bitmap� gracza.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj�cy bitmap� gracza.
 */
void Engine::Player::setPlayerBitmap(BitmapHandler bitmap) {
	this->playerBitmap = bitmap;
}

/**
 * @brief Ustawia aktualn� pozycj� gracza.
 *
 * @param position Nowa pozycja gracza.
 */
void Engine::Player::setActualPosition(Vector2f position, string positionSite) {
	Vector2f topPosition(position.x, position.y);
	Vector2f leftPosition(position.x, position.y);
	Vector2f rightPosition(position.x, position.y);
	Vector2f shoePosition(position.x, position.y);
	if (positionSite == "left") {
		topPosition.x += 20.0f;
		rightPosition.x += 20.0f;
		shoePosition.x += 155.0f;
		shoePosition.y += 100.0f;
	}
	else {
		topPosition.x += 40.0f;
		leftPosition.x += 40.0f;
		rightPosition.x += 150.0f;
		shoePosition.x += 35.0f;
		shoePosition.y += 155.0f;
	}
	FloatRect topRect(topPosition, Vector2f(125.0f, 25.0f));
	FloatRect leftRect(leftPosition, Vector2f((getInstance().window->getSize().x) / 8.0f, 
		(getInstance().window->getSize().y) / 4.0f));
	FloatRect rightRect(rightPosition, Vector2f(10.0f, 140.0f));
	FloatRect shoeRect(shoePosition, Vector2f(50.0f, 50.0f));
	this->position = position;
	this->topRect = topRect;
	this->leftRect = leftRect;
	this->rightRect = rightRect;
	this->shoeRect = shoeRect;
}

/**
 * @brief Pobiera aktualn� pr�dko�� gracza.
 *
 * @return Aktualna pr�dko�� gracza.
 */
float Engine::Player::getActualSpeed() {
	return this->actualSpeed;
}

/**
 * @brief Pobiera aktualn� pozycj� gracza.
 *
 * @return Obiekt Vector2f reprezentuj�cy aktualn� pozycj� gracza.
 */
Vector2f Engine::Player::getActualPosition() {
	return this->position;
}

/**
 * @brief Pobiera bitmap� gracza.
 *
 * @return Obiekt BitmapHandler reprezentuj�cy bitmap� gracza.
 */
Engine::BitmapHandler Engine::Player::getPlayerBitmap() {
	return this->playerBitmap;
}