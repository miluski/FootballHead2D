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
void Engine::Player::setActualPosition(Vector2f position) {
	this->position = position;
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