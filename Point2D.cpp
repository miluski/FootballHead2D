#include "Engine.hpp"

using namespace Game;

/**
 * @brief Domyœlny konstruktor obiektu Point2D ustawiaj¹cy wspó³rzêdne na (0, 0).
 */
Point2D::Point2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

/**
 * @brief Konstruktor obiektu Point2D z zadanymi wspó³rzêdnymi.
 *
 * @param x Wspó³rzêdna X punktu.
 * @param y Wspó³rzêdna Y punktu.
 */
Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

/**
 * @brief Konstruktor obiektu Point2D z zadanym kolorem piksela i wspó³rzêdnymi.
 *
 * @param pixelColor Kolor piksela.
 * @param x Wspó³rzêdna X punktu.
 * @param y Wspó³rzêdna Y punktu.
 */
Point2D::Point2D(Color pixelColor, float x, float y) {
	this->pixelColor = pixelColor;
	this->x = x;
	this->y = y;
}

/**
 * @brief Pobiera wspó³rzêdn¹ X punktu.
 *
 * @return Aktualna wspó³rzêdna X.
 */
float Point2D::getX() {
	return this->x;
}

/**
 * @brief Pobiera wspó³rzêdn¹ Y punktu.
 *
 * @return Aktualna wspó³rzêdna Y.
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
 * @brief Ustawia wspó³rzêdne punktu.
 *
 * @param x Nowa wspó³rzêdna X punktu.
 * @param y Nowa wspó³rzêdna Y punktu.
 */
void Point2D::setCoords(float x, float y) {
	this->x = x;
	this->y = y;
}

/**
 * @brief Rysuje punkt na ekranie za pomoc¹ PrimitiveRenderer.
 */
void Point2D::draw() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawCircle(1.0f, Vector2f(this->x, this->y), pixelColor);
}