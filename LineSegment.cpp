#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor obiektu LineSegment ustawiaj�cy punkty pocz�tkowy i ko�cowy odcinka.
 *
 * @param startPoint Punkt pocz�tkowy odcinka.
 * @param endPoint Punkt ko�cowy odcinka.
 */
LineSegment::LineSegment(Point2D startPoint, Point2D endPoint) {
	this->startPoint = startPoint;
	this->endPoint = endPoint;
}

/**
 * @brief Pobiera punkt pocz�tkowy odcinka LineSegment.
 *
 * @return Punkt pocz�tkowy odcinka.
 */
Point2D LineSegment::getStartPoint() {
	return startPoint;
}

/**
 * @brief Pobiera punkt ko�cowy odcinka LineSegment.
 *
 * @return Punkt ko�cowy odcinka.
 */
Point2D LineSegment::getEndPoint() {
	return endPoint;
}

/**
 * @brief Ustawia nowy punkt pocz�tkowy odcinka LineSegment.
 *
 * @param startPoint Nowy punkt pocz�tkowy odcinka.
 */
void LineSegment::setStartPoint(Point2D startPoint) {
	this->startPoint = startPoint;
}

/**
 * @brief Ustawia nowy punkt ko�cowy odcinka LineSegment.
 *
 * @param endPoint Nowy punkt ko�cowy odcinka.
 */
void LineSegment::setEndPoint(Point2D endPoint) {
	this->endPoint = endPoint;
}

/**
 * @brief Rysuje odcinek na ekranie w podanym kolorze.
 *
 * @param color Kolor do u�ycia podczas rysowania odcinka.
 */
void LineSegment::draw(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

/**
 * @brief Rysuje powi�kszony odcinek na ekranie w podanym kolorze.
 *
 * @param color Kolor do u�ycia podczas rysowania odcinka.
 */
void LineSegment::drawIncreased(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawIncreasedLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

