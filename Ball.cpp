#include "Engine.hpp"

using namespace Game;

void Engine::Ball::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}
void Engine::Ball::setBallBitmap(BitmapHandler bitmap) {
	this->ballBitmap = bitmap;
}
void Engine::Ball::setActualPosition(Vector2f position) {
	this->position = position;
}
float Engine::Ball::getActualSpeed() {
	return this->actualSpeed;
}
Vector2f Engine::Ball::getActualPosition() {
	return this->position;
}
Engine::BitmapHandler Engine::Ball::getBallBitmap() {
	return this->ballBitmap;
}