#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor klasy Triangle inicjalizuj¹cy trójk¹t o okreœlonym promieniu.
 * @param radius Promieñ trójk¹ta.
 */
Engine::Triangle::Triangle(float radius) {
	this->triangle.setRadius(radius);
	this->triangle.setPointCount(3);
	this->triangle.setPosition(getX(), getY());
}

/**
 * @brief Metoda rysuj¹ca trójk¹t na g³ównym oknie.
 */
void Engine::Triangle::draw() {
	getInstance().getMainWindow()->draw(triangle);
}

/**
 * @brief Metoda przesuwaj¹ca trójk¹t do okreœlonej pozycji.
 * @param position Nowa pozycja trójk¹ta.
 */
void Engine::Triangle::translate(Vector2f position) {
	this->triangle.setPosition(position);
}

/**
 * @brief Metoda obracaj¹ca trójk¹t o okreœlony k¹t.
 * @param angle K¹t obrotu w stopniach.
 */
void Engine::Triangle::rotate(float angle) {
	this->triangle.rotate(angle);
}

/**
 * @brief Metoda skaluj¹ca trójk¹t o okreœlony wspó³czynnik.
 * @param scale Wspó³czynniki skalowania wzd³u¿ osi X i Y.
 */
void Engine::Triangle::scale(Vector2f scale) {
	this->triangle.setScale(scale);
}

/**
 * @brief Metoda ustawiaj¹ca kolor wype³nienia trójk¹ta.
 * @param color Kolor wype³nienia trójk¹ta.
 */
void Engine::Triangle::setColor(Color color) {
	this->triangle.setFillColor(color);
}

/**
 * @brief Metoda zwracaj¹ca aktualny kolor wype³nienia trójk¹ta.
 * @return Kolor wype³nienia trójk¹ta.
 */
Color Engine::Triangle::getColor() {
	return this->triangle.getFillColor();
}