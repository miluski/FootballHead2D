#include "Engine.hpp"

using namespace Game;

/**
 * @brief Ustawia rzeczywist¹ prêdkoœæ pi³ki.
 *
 * @param speed Prêdkoœæ do ustawienia dla pi³ki.
 */
void Engine::Ball::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}

/**
 * @brief Ustawia bitmapê dla pi³ki.
 *
 * @param bitmap Obiekt BitmapHandler reprezentuj¹cy bitmapê pi³ki.
 */
void Engine::Ball::setBallBitmap(BitmapHandler bitmap) {
	this->ballBitmap = bitmap;
}

/**
 * @brief Ustawia rzeczywist¹ pozycjê pi³ki.
 *
 * @param position Obiekt Vector2f reprezentuj¹cy pozycjê pi³ki.
 */
void Engine::Ball::setActualPosition(Vector2f position) {
	this->position = position;
}

/**
 * @brief Pobiera rzeczywist¹ prêdkoœæ pi³ki.
 *
 * @return Rzeczywista prêdkoœæ pi³ki.
 */
float Engine::Ball::getActualSpeed() {
	return this->actualSpeed;
}

/**
 * @brief Pobiera rzeczywist¹ pozycjê pi³ki.
 *
 * @return Obiekt Vector2f reprezentuj¹cy pozycjê pi³ki.
 */
Vector2f Engine::Ball::getActualPosition() {
	return this->position;
}

/**
 * @brief Pobiera bitmapê pi³ki.
 *
 * @return Obiekt BitmapHandler reprezentuj¹cy bitmapê pi³ki.
 */
Engine::BitmapHandler Engine::Ball::getBallBitmap() {
	return this->ballBitmap;
}