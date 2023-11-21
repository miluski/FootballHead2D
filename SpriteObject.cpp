#include "Engine.hpp"

using namespace Game;

Engine::SpriteObject::SpriteObject() {
}

Engine::SpriteObject::SpriteObject(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

void Engine::SpriteObject::createSpriteFrom(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

void Engine::SpriteObject::createSpriteFrom(Texture* bitmap[], int bitmapArraySize, Vector2f positions[], Vector2f scales[]) {
	getInstance().backgroundRenderTexture->clear();
	for (int i = 0; i < bitmapArraySize; i++) {
		Sprite bufferSprite;
		bufferSprite.setTexture(*bitmap[i]);
		bufferSprite.setPosition(positions[i].x, positions[i].y);
		bufferSprite.setScale(scales[i].x, scales[i].y);
		getInstance().backgroundRenderTexture->draw(bufferSprite);
	}
}

void Engine::SpriteObject::setCollisionRect(IntRect collisionRect) {
	this->spriteObject.setTextureRect(collisionRect);
}

void Engine::SpriteObject::animate(BitmapHandler bitmap, Player* player) {
	player->setPlayerBitmap(bitmap);
}