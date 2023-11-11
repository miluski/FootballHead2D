#include "Engine.hpp"

using namespace Game;

Engine::Player::Player() {

}

void Engine::Player::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}
void Engine::Player::setPlayerTexture(string fileName) {
	this->playerTexture.loadFromFile(fileName);
	this->playerTexture.setSmooth(true);
}
void Engine::Player::setActualPosition(Vector2f position) {
	this->position = position;
}
float Engine::Player::getActualSpeed() {
	return this->actualSpeed;
}
Vector2f Engine::Player::getActualPosition() {
	return this->position;
}
Texture Engine::Player::getPlayerTexture() {
	return this->playerTexture;
}