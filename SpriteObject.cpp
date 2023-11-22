#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor domyœlny klasy SpriteObject.
 */
Engine::SpriteObject::SpriteObject() {
}

/**
 * @brief Konstruktor klasy SpriteObject inicjalizuj¹cy obiekt sprite za pomoc¹ tekstury, pozycji i skali.
 * @param bitmap WskaŸnik do tekstury obiektu sprite.
 * @param position Pozycja pocz¹tkowa obiektu sprite.
 * @param scale Skala obiektu sprite.
 */
Engine::SpriteObject::SpriteObject(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

/**
 * @brief Metoda tworz¹ca obiekt sprite na podstawie tekstury, pozycji i skali.
 * @param bitmap WskaŸnik do tekstury obiektu sprite.
 * @param position Pozycja pocz¹tkowa obiektu sprite.
 * @param scale Skala obiektu sprite.
 */
void Engine::SpriteObject::createSpriteFrom(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

/**
 * @brief Metoda tworz¹ca obiekty sprite z tablicy tekstur, pozycji i skali.
 * @param bitmap WskaŸniki do tekstur obiektów sprite.
 * @param bitmapArraySize Rozmiar tablicy tekstur.
 * @param positions Pozycje pocz¹tkowe obiektów sprite.
 * @param scales Skale obiektów sprite.
 */
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

/**
 * @brief Metoda ustawiaj¹ca prostok¹t kolizji dla obiektu sprite.
 * @param collisionRect Prostok¹t kolizji w obrêbie tekstury obiektu sprite.
 */
void Engine::SpriteObject::setCollisionRect(IntRect collisionRect) {
	this->spriteObject.setTextureRect(collisionRect);
}

/**
 * @brief Metoda wykonuj¹ca animacjê obiektu sprite na podstawie handlera bitmapy i obiektu gracza.
 * @param bitmap Handler bitmapy u¿ywanej do animacji.
 * @param player WskaŸnik do obiektu gracza, którego animacja ma byæ zmieniona.
 */
void Engine::SpriteObject::animate(BitmapHandler bitmap, Player* player) {
	player->setPlayerBitmap(bitmap);
}