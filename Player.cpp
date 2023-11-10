#include "Engine.hpp"

Player::Player(float x, float y, Sprite playerTexture) {
	setX(x);
	setY(y);
	this->actualSpeed = 0.0f;
	this->playerTexture = playerTexture;
}
void Player::setActualSpeed(float speed) {
	this->actualSpeed = speed;
}
void Player::setPlayerTexture(Sprite playerTexture) {
	this->playerTexture = playerTexture;
}
float Player::getActualSpeed() {
	return this->actualSpeed;
}
Sprite Player::getPlayerTexture() {
	return this->playerTexture;
}