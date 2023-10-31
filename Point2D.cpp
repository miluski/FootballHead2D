#include "Engine.hpp"

float Point2D::getX() {
	return this->x;
}

float Point2D::getY() {
	return this->y;
}

void Point2D::setCoords(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point2D::drawPoint() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawCircle(1.0f, Vector2f(this->x, this->y), Color::Black);
}