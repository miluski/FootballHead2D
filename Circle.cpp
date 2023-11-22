#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor obiektu Circle ustawiaj�cy promie� ko�a.
 *
 * @param radius Promie� ko�a.
 */
Engine::Circle::Circle(float radius) {
	this->circle.setRadius(radius);
	this->circle.setPosition(getX(), getY());
}

/**
 * @brief Rysuje obiekt Circle na ekranie.
 *
 * Metoda ta korzysta z g��wnego okna aplikacji do narysowania ko�a.
 */
void Engine::Circle::draw() {
	getInstance().getMainWindow()->draw(circle);
}

/**
 * @brief Przesuwa ko�o do podanej pozycji.
 *
 * @param position Nowa pozycja ko�a.
 */
void Engine::Circle::translate(Vector2f position) {
	this->circle.setPosition(position);
}

/**
 * @brief Obraca ko�o o podany k�t.
 *
 * @param angle K�t rotacji.
 */
void Engine::Circle::rotate(float angle) {
	this->circle.rotate(angle);
}

/**
 * @brief Skaluje ko�o na podstawie podanego wektora skali.
 *
 * @param scale Wektor skali.
 */
void Engine::Circle::scale(Vector2f scale) {
	this->circle.setScale(scale);
}

/**
 * @brief Ustawia kolor wype�nienia ko�a.
 *
 * @param color Kolor wype�nienia ko�a.
 */
void Engine::Circle::setColor(Color color) {
	this->circle.setFillColor(color);
}

/**
 * @brief Pobiera aktualny kolor wype�nienia ko�a.
 *
 * @return Kolor wype�nienia ko�a.
 */
Color Engine::Circle::getColor() {
	return this->circle.getFillColor();
}