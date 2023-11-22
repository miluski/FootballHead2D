#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor domyœlny klasy Rectangle.
 */
Engine::Rectangle::Rectangle() {
}

/**
 * @brief Konstruktor klasy Rectangle z okreœlonym rozmiarem.
 * @param size Rozmiar prostok¹ta.
 */
Engine::Rectangle::Rectangle(Vector2f size) {
	this->rectangle.setSize(size);
}

/**
 * @brief Metoda rysuj¹ca prostok¹t na g³ównym oknie.
 */
void Engine::Rectangle::draw() {
	getInstance().getMainWindow()->draw(rectangle);
}

/**
 * @brief Metoda przesuwaj¹ca prostok¹t do okreœlonej pozycji.
 * @param position Nowa pozycja prostok¹ta.
 */
void Engine::Rectangle::translate(Vector2f position) {
	this->rectangle.setPosition(position);
}

/**
 * @brief Metoda obracaj¹ca prostok¹t o okreœlony k¹t.
 * @param angle K¹t obrotu w stopniach.
 */
void Engine::Rectangle::rotate(float angle) {
	this->rectangle.rotate(angle);
}

/**
 * @brief Metoda skaluj¹ca prostok¹t o okreœlony wspó³czynnik.
 * @param scale Wspó³czynniki skalowania wzd³u¿ osi X i Y.
 */
void Engine::Rectangle::scale(Vector2f scale) {
	this->rectangle.setScale(scale);
}

/**
 * @brief Metoda ustawiaj¹ca kolor wype³nienia prostok¹ta.
 * @param color Kolor wype³nienia prostok¹ta.
 */
void Engine::Rectangle::setColor(Color color) {
	this->rectangle.setFillColor(color);
}

/**
 * @brief Metoda zwracaj¹ca aktualny kolor wype³nienia prostok¹ta.
 * @return Kolor wype³nienia prostok¹ta.
 */
Color Engine::Rectangle::getColor() {
	return this->rectangle.getFillColor();
}