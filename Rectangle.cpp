#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor domy�lny klasy Rectangle.
 */
Engine::Rectangle::Rectangle() {
}

/**
 * @brief Konstruktor klasy Rectangle z okre�lonym rozmiarem.
 * @param size Rozmiar prostok�ta.
 */
Engine::Rectangle::Rectangle(Vector2f size) {
	this->rectangle.setSize(size);
}

/**
 * @brief Metoda rysuj�ca prostok�t na g��wnym oknie.
 */
void Engine::Rectangle::draw() {
	getInstance().getMainWindow()->draw(rectangle);
}

/**
 * @brief Metoda przesuwaj�ca prostok�t do okre�lonej pozycji.
 * @param position Nowa pozycja prostok�ta.
 */
void Engine::Rectangle::translate(Vector2f position) {
	this->rectangle.setPosition(position);
}

/**
 * @brief Metoda obracaj�ca prostok�t o okre�lony k�t.
 * @param angle K�t obrotu w stopniach.
 */
void Engine::Rectangle::rotate(float angle) {
	this->rectangle.rotate(angle);
}

/**
 * @brief Metoda skaluj�ca prostok�t o okre�lony wsp�czynnik.
 * @param scale Wsp�czynniki skalowania wzd�u� osi X i Y.
 */
void Engine::Rectangle::scale(Vector2f scale) {
	this->rectangle.setScale(scale);
}

/**
 * @brief Metoda ustawiaj�ca kolor wype�nienia prostok�ta.
 * @param color Kolor wype�nienia prostok�ta.
 */
void Engine::Rectangle::setColor(Color color) {
	this->rectangle.setFillColor(color);
}

/**
 * @brief Metoda zwracaj�ca aktualny kolor wype�nienia prostok�ta.
 * @return Kolor wype�nienia prostok�ta.
 */
Color Engine::Rectangle::getColor() {
	return this->rectangle.getFillColor();
}