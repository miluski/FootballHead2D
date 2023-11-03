#include "Engine.hpp"

LineSegment::LineSegment(Point2D startPoint, Point2D endPoint) {
	this->startPoint = startPoint;
	this->endPoint = endPoint;
}

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

void LineSegment::draw(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

void LineSegment::drawIncreased(Color color) {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawIncreasedLine(Vector2f(startPoint.getX(), startPoint.getY()), Vector2f(endPoint.getX(), endPoint.getY()), color);
}

