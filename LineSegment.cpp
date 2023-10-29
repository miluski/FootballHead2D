#include "Engine.hpp"

Point2D LineSegment::getStartPoint() {
	return startPoint;
}

Point2D LineSegment::getEndPoint() {
	return endPoint;
}

void LineSegment::setStartPoint(Point2D startPoint) {
	this->startPoint = startPoint;
}

void LineSegment::setEndPoint(Point2D endPoint) {
	this->endPoint = endPoint;
}

void LineSegment::drawLine() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), Color::Black);
}

void LineSegment::drawIncreasedLine() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawIncreasedLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), Color::Black);
}

