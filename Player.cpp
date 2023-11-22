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
void Engine::Player::setActualPosition(Vector2f position) {
	this->position = position;
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