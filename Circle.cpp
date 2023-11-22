#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor obiektu Circle ustawiaj¹cy promieñ ko³a.
 *
 * @param radius Promieñ ko³a.
 */
Engine::Circle::Circle(float radius) {
	this->circle.setRadius(radius);
	this->circle.setPosition(getX(), getY());
}

/**
 * @brief Rysuje obiekt Circle na ekranie.
 *
 * Metoda ta korzysta z g³ównego okna aplikacji do narysowania ko³a.
 */
void Engine::Circle::draw() {
	getInstance().getMainWindow()->draw(circle);
}

/**
 * @brief Przesuwa ko³o do podanej pozycji.
 *
 * @param position Nowa pozycja ko³a.
 */
void Engine::Circle::translate(Vector2f position) {
	this->circle.setPosition(position);
}

/**
 * @brief Obraca ko³o o podany k¹t.
 *
 * @param angle K¹t rotacji.
 */
void Engine::Circle::rotate(float angle) {
	this->circle.rotate(angle);
}

/**
 * @brief Skaluje ko³o na podstawie podanego wektora skali.
 *
 * @param scale Wektor skali.
 */
void Engine::Circle::scale(Vector2f scale) {
	this->circle.setScale(scale);
}

/**
 * @brief Ustawia kolor wype³nienia ko³a.
 *
 * @param color Kolor wype³nienia ko³a.
 */
void Engine::Circle::setColor(Color color) {
	this->circle.setFillColor(color);
}

/**
 * @brief Pobiera aktualny kolor wype³nienia ko³a.
 *
 * @return Kolor wype³nienia ko³a.
 */
Color Engine::Circle::getColor() {
	return this->circle.getFillColor();
}