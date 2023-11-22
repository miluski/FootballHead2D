#include "Engine.hpp"

using namespace Game;

/**
 * @brief Ustawia rzeczywist� pr�dko�� pi�ki.
 *
 * @param speed Pr�dko�� do ustawienia dla pi�ki.
 */
void Engine::Ball::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}

/**
 * @brief Ustawia bitmap� dla pi�ki.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj�cy bitmap� pi�ki.
 */
void Engine::Ball::setBallBitmap(BitmapHandler bitmap) {
	this->ballBitmap = bitmap;
}

/**
 * @brief Ustawia rzeczywist� pozycj� pi�ki.
 *
 * @param position Obiekt Vector2f reprezentuj�cy pozycj� pi�ki.
 */
void Engine::Ball::setActualPosition(Vector2f position) {
	this->position = position;
}

/**
 * @brief Pobiera rzeczywist� pr�dko�� pi�ki.
 *
 * @return Rzeczywista pr�dko�� pi�ki.
 */
float Engine::Ball::getActualSpeed() {
	return this->actualSpeed;
}

/**
 * @brief Pobiera rzeczywist� pozycj� pi�ki.
 *
 * @return Obiekt Vector2f reprezentuj�cy pozycj� pi�ki.
 */
Vector2f Engine::Ball::getActualPosition() {
	return this->position;
}

/**
 * @brief Pobiera bitmap� pi�ki.
 *
 * @return Obiekt BitmapHandler reprezentuj�cy bitmap� pi�ki.
 */
Engine::BitmapHandler Engine::Ball::getBallBitmap() {
	return this->ballBitmap;
}