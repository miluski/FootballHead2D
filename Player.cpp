#include "Engine.hpp"

using namespace Game;

void Engine::Player::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}
void Engine::Player::setPlayerBitmap(BitmapHandler bitmap) {
	this->playerBitmap = bitmap;
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
Engine::BitmapHandler Engine::Player::getPlayerBitmap() {
	return this->playerBitmap;
}