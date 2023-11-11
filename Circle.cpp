#include "Engine.hpp"

using namespace Game;

Engine::Circle::Circle(float radius) {
	this->circle.setRadius(radius);
	this->circle.setPosition(getX(), getY());
}

void Engine::Circle::draw() {
	getInstance().getMainWindow()->draw(circle);
}

void Engine::Circle::translate(Vector2f position) {
	this->circle.setPosition(position);
}

void Engine::Circle::rotate(float angle) {
	this->circle.rotate(angle);
}

void Engine::Circle::scale(Vector2f scale) {
	this->circle.setScale(scale);
}

void Engine::Circle::setColor(Color color) {
	this->circle.setFillColor(color);
}

Color Engine::Circle::getColor() {
	return this->circle.getFillColor();
}