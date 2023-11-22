#include "Engine.hpp"

using namespace Game;

/**
 * @brief Rysuje obiekt bitmapowy na ekranie.
 *
 * Metoda ta u¿ywa obiektu RenderTexture do renderowania t³a i nastêpnie przypisuje
 * uzyskan¹ teksturê obiektowi spriteObject, który jest u¿ywany do rysowania na ekranie.
 */
void Engine::BitmapObject::draw() {
	getInstance().backgroundRenderTexture->display();
	this->spriteObject.setTexture(getInstance().backgroundRenderTexture->getTexture());
	getInstance().setMainBufferTexture(this->spriteObject);
	getInstance().setSecondBufferTexture(this->spriteObject);
	getInstance().handleBuffers();
}

/**
 * @brief Pobiera obiekt sprite reprezentuj¹cy bitmapê.
 *
 * @return Obiekt sprite reprezentuj¹cy bitmapê.
 */
Sprite Engine::BitmapObject::getSprite() {
	return this->spriteObject;
}