#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor obiektu LineSegment ustawiaj¹cy punkty pocz¹tkowy i koñcowy odcinka.
 *
 * @param startPoint Punkt pocz¹tkowy odcinka.
 * @param endPoint Punkt koñcowy odcinka.
 */
LineSegment::LineSegment(Point2D startPoint, Point2D endPoint) {
	this->startPoint = startPoint;
	this->endPoint = endPoint;
}

/**
 * @brief Pobiera punkt pocz¹tkowy odcinka LineSegment.
 *
 * @return Punkt pocz¹tkowy odcinka.
 */
Point2D LineSegment::getStartPoint() {
	return startPoint;
}

/**
 * @brief Pobiera punkt koñcowy odcinka LineSegment.
 *
 * @return Punkt koñcowy odcinka.
 */
Point2D LineSegment::getEndPoint() {
	return endPoint;
}

/**
 * @brief Ustawia nowy punkt pocz¹tkowy odcinka LineSegment.
 *
 * @param startPoint Nowy punkt pocz¹tkowy odcinka.
 */
void LineSegment::setStartPoint(Point2D startPoint) {
	this->startPoint = startPoint;
}

/**
 * @brief Ustawia nowy punkt koñcowy odcinka LineSegment.
 *
 * @param endPoint Nowy punkt koñcowy odcinka.
 */
void LineSegment::setEndPoint(Point2D endPoint) {
	this->endPoint = endPoint;
}

/**
 * @brief Rysuje odcinek na ekranie w podanym kolorze.
 *
 * @param color Kolor do u¿ycia podczas rysowania odcinka.
 */
void LineSegment::draw(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

/**
 * @brief Rysuje powiêkszony odcinek na ekranie w podanym kolorze.
 *
 * @param color Kolor do u¿ycia podczas rysowania odcinka.
 */
void LineSegment::drawIncreased(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawIncreasedLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

