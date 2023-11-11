#include "Engine.hpp"

using namespace Game;

Point2D::Point2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Point2D::Point2D(Color pixelColor, float x, float y) {
	this->pixelColor = pixelColor;
	this->x = x;
	this->y = y;
}

float Point2D::getX() {
	return this->x;
}

float Point2D::getY() {
	return this->y;
}

Color Point2D::getPixelColor() {
	return Color::Transparent;
}

void Point2D::setPixelColor(Color pixelColor) {
	this->pixelColor = pixelColor;
}

void Point2D::setCoords(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point2D::draw() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawCircle(1.0f, Vector2f(this->x, this->y), pixelColor);
}