#include "Engine.hpp"

using namespace Game;

Engine::Rectangle::Rectangle() {
}

Engine::Rectangle::Rectangle(Vector2f size) {
	this->rectangle.setSize(size);
}

void Engine::Rectangle::draw() {
	getInstance().getMainWindow()->draw(rectangle);
}

void Engine::Rectangle::translate(Vector2f position) {
	this->rectangle.setPosition(position);
}

void Engine::Rectangle::rotate(float angle) {
	this->rectangle.rotate(angle);
}

void Engine::Rectangle::scale(Vector2f scale) {
	this->rectangle.setScale(scale);
}

void Engine::Rectangle::setColor(Color color) {
	this->rectangle.setFillColor(color);
}

Color Engine::Rectangle::getColor() {
	return this->rectangle.getFillColor();
}