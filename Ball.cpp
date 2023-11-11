#include "Engine.hpp"

using namespace Game;

Engine::Ball::Ball() {

}

void Engine::Ball::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}
void Engine::Ball::setBallTexture(string fileName) {
	this->ballTexture.loadFromFile(fileName);
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
Texture Engine::Ball::getBallTexture() {
	return this->ballTexture;
}