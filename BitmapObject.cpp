#include "Engine.hpp"

using namespace Game;

void Engine::BitmapObject::draw() {
	getInstance().backgroundRenderTexture->display();
	this->spriteObject.setTexture(getInstance().backgroundRenderTexture->getTexture());
	getInstance().setMainBufferTexture(this->spriteObject);
	getInstance().setSecondBufferTexture(this->spriteObject);
	getInstance().handleBuffers();
}

Sprite Engine::BitmapObject::getSprite() {
	return this->spriteObject;
}