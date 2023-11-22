#include "Engine.hpp"

using namespace Game;

/**
 * @brief Domy�lny konstruktor obiektu Point2D ustawiaj�cy wsp�rz�dne na (0, 0).
 */
Point2D::Point2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

/**
 * @brief Konstruktor obiektu Point2D z zadanymi wsp�rz�dnymi.
 *
 * @param x Wsp�rz�dna X punktu.
 * @param y Wsp�rz�dna Y punktu.
 */
Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

/**
 * @brief Konstruktor obiektu Point2D z zadanym kolorem piksela i wsp�rz�dnymi.
 *
 * @param pixelColor Kolor piksela.
 * @param x Wsp�rz�dna X punktu.
 * @param y Wsp�rz�dna Y punktu.
 */
Point2D::Point2D(Color pixelColor, float x, float y) {
	this->pixelColor = pixelColor;
	this->x = x;
	this->y = y;
}

/**
 * @brief Pobiera wsp�rz�dn� X punktu.
 *
 * @return Aktualna wsp�rz�dna X.
 */
float Point2D::getX() {
	return this->x;
}

/**
 * @brief Pobiera wsp�rz�dn� Y punktu.
 *
 * @return Aktualna wsp�rz�dna Y.
 */
float Point2D::getY() {
	return this->y;
}

/**
 * @brief Pobiera kolor piksela punktu.
 *
 * @return Kolor piksela punktu.
 */
Color Point2D::getPixelColor() {
	return Color::Transparent;
}

/**
 * @brief Ustawia kolor piksela punktu.
 *
 * @param pixelColor Nowy kolor piksela.
 */
void Point2D::setPixelColor(Color pixelColor) {
	this->pixelColor = pixelColor;
}

/**
 * @brief Ustawia wsp�rz�dne punktu.
 *
 * @param x Nowa wsp�rz�dna X punktu.
 * @param y Nowa wsp�rz�dna Y punktu.
 */
void Point2D::setCoords(float x, float y) {
	this->x = x;
	this->y = y;
}

/**
 * @brief Rysuje punkt na ekranie za pomoc� PrimitiveRenderer.
 */
void Point2D::draw() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawCircle(1.0f, Vector2f(this->x, this->y), pixelColor);
}