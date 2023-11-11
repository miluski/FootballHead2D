#include "Engine.hpp"

using namespace Game;

Engine::Triangle::Triangle(float radius) {
	this->triangle.setRadius(radius);
	this->triangle.setPointCount(3);
	this->triangle.setPosition(getX(), getY());
}

void Engine::Triangle::draw() {
	getInstance().getMainWindow()->draw(triangle);
}

void Engine::Triangle::translate(Vector2f position) {
	this->triangle.setPosition(position);
}

void Engine::Triangle::rotate(float angle) {
	this->triangle.rotate(angle);
}

void Engine::Triangle::scale(Vector2f scale) {
	this->triangle.setScale(scale);
}

void Engine::Triangle::setColor(Color color) {
	this->triangle.setFillColor(color);
}

Color Engine::Triangle::getColor() {
	return this->triangle.getFillColor();
}