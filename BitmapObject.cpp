#include "Engine.hpp"

using namespace Game;

/**
 * @brief Rysuje obiekt bitmapowy na ekranie.
 *
 * Metoda ta u�ywa obiektu RenderTexture do renderowania t�a i nast�pnie przypisuje
 * uzyskan� tekstur� obiektowi spriteObject, kt�ry jest u�ywany do rysowania na ekranie.
 */
void Engine::BitmapObject::draw() {
	getInstance().backgroundRenderTexture->display();
	this->spriteObject.setTexture(getInstance().backgroundRenderTexture->getTexture());
	getInstance().setMainBufferTexture(this->spriteObject);
	getInstance().setSecondBufferTexture(this->spriteObject);
	getInstance().handleBuffers();
}

/**
 * @brief Pobiera obiekt sprite reprezentuj�cy bitmap�.
 *
 * @return Obiekt sprite reprezentuj�cy bitmap�.
 */
Sprite Engine::BitmapObject::getSprite() {
	return this->spriteObject;
}