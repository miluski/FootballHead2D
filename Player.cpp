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
 * @brief Ustawia bitmap� dla wy��czonego gracza.
 *
 * Funkcja ustawia bitmap� dla przypadku, gdy gracz jest wy��czony.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj�cy bitmap� dla wy��czonego gracza.
 */
void Engine::Player::setPlayerDisabledBitmap(BitmapHandler bitmap) {
	this->playerDisabledBitmap = bitmap;
}

/**
 * @brief Ustawia bitmap� dla zamro�onego gracza.
 *
 * Funkcja ustawia bitmap� dla przypadku, gdy gracz jest zamro�ony.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj�cy bitmap� dla zamro�onego gracza.
 */
void Engine::Player::setPlayerFreezedBitmap(BitmapHandler bitmap) {
	this->playerFreezedBitmap = bitmap;
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
		topPosition.x += 65.0f;
		leftPosition.x += 35.0f;
		leftPosition.y += 30.0f;
		rightPosition.x += 20.0f;
		shoePosition.x += 85.0f;
		shoePosition.y += 120.0f;
	}
	else {
		topPosition.x += 65.0f;
		leftPosition.x += 45.0f;
		leftPosition.y += 30.0f;
		rightPosition.x += 150.0f;
		shoePosition.x += 25.0f;
		shoePosition.y += 120.0f;
	}
	FloatRect topRect(topPosition, Vector2f(75.0f, 25.0f));
	FloatRect leftRect(leftPosition, Vector2f((getInstance().window->getSize().x) / 12.5f, 
		(getInstance().window->getSize().y) / 7.0f));
	FloatRect rightRect(rightPosition, Vector2f(30.0f, 140.0f));
	FloatRect shoeRect(shoePosition, Vector2f(100.0f, 100.0f));
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
	if (!this->isDisabled && !this->isFreezed)
		return this->playerBitmap;
	else if (this->isDisabled)
		return this->playerDisabledBitmap;
	else
		return this->playerFreezedBitmap;
}