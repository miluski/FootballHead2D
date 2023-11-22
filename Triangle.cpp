#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor klasy Triangle inicjalizuj�cy tr�jk�t o okre�lonym promieniu.
 * @param radius Promie� tr�jk�ta.
 */
Engine::Triangle::Triangle(float radius) {
	this->triangle.setRadius(radius);
	this->triangle.setPointCount(3);
	this->triangle.setPosition(getX(), getY());
}

/**
 * @brief Metoda rysuj�ca tr�jk�t na g��wnym oknie.
 */
void Engine::Triangle::draw() {
	getInstance().getMainWindow()->draw(triangle);
}

/**
 * @brief Metoda przesuwaj�ca tr�jk�t do okre�lonej pozycji.
 * @param position Nowa pozycja tr�jk�ta.
 */
void Engine::Triangle::translate(Vector2f position) {
	this->triangle.setPosition(position);
}

/**
 * @brief Metoda obracaj�ca tr�jk�t o okre�lony k�t.
 * @param angle K�t obrotu w stopniach.
 */
void Engine::Triangle::rotate(float angle) {
	this->triangle.rotate(angle);
}

/**
 * @brief Metoda skaluj�ca tr�jk�t o okre�lony wsp�czynnik.
 * @param scale Wsp�czynniki skalowania wzd�u� osi X i Y.
 */
void Engine::Triangle::scale(Vector2f scale) {
	this->triangle.setScale(scale);
}

/**
 * @brief Metoda ustawiaj�ca kolor wype�nienia tr�jk�ta.
 * @param color Kolor wype�nienia tr�jk�ta.
 */
void Engine::Triangle::setColor(Color color) {
	this->triangle.setFillColor(color);
}

/**
 * @brief Metoda zwracaj�ca aktualny kolor wype�nienia tr�jk�ta.
 * @return Kolor wype�nienia tr�jk�ta.
 */
Color Engine::Triangle::getColor() {
	return this->triangle.getFillColor();
}