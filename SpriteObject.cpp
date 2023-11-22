#include "Engine.hpp"

using namespace Game;

/**
 * @brief Konstruktor domy�lny klasy SpriteObject.
 */
Engine::SpriteObject::SpriteObject() {
}

/**
 * @brief Konstruktor klasy SpriteObject inicjalizuj�cy obiekt sprite za pomoc� tekstury, pozycji i skali.
 * @param bitmap Wska�nik do tekstury obiektu sprite.
 * @param position Pozycja pocz�tkowa obiektu sprite.
 * @param scale Skala obiektu sprite.
 */
Engine::SpriteObject::SpriteObject(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

/**
 * @brief Metoda tworz�ca obiekt sprite na podstawie tekstury, pozycji i skali.
 * @param bitmap Wska�nik do tekstury obiektu sprite.
 * @param position Pozycja pocz�tkowa obiektu sprite.
 * @param scale Skala obiektu sprite.
 */
void Engine::SpriteObject::createSpriteFrom(Texture* bitmap, Vector2f position, Vector2f scale) {
	this->spriteObject.setTexture(*bitmap);
	this->spriteObject.setPosition(position.x, position.y);
	this->spriteObject.setScale(scale.x, scale.y);
	getInstance().backgroundRenderTexture->draw(this->spriteObject);
}

/**
 * @brief Metoda tworz�ca obiekty sprite z tablicy tekstur, pozycji i skali.
 * @param bitmap Wska�niki do tekstur obiekt�w sprite.
 * @param bitmapArraySize Rozmiar tablicy tekstur.
 * @param positions Pozycje pocz�tkowe obiekt�w sprite.
 * @param scales Skale obiekt�w sprite.
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
 * @brief Metoda ustawiaj�ca prostok�t kolizji dla obiektu sprite.
 * @param collisionRect Prostok�t kolizji w obr�bie tekstury obiektu sprite.
 */
void Engine::SpriteObject::setCollisionRect(IntRect collisionRect) {
	this->spriteObject.setTextureRect(collisionRect);
}

/**
 * @brief Metoda wykonuj�ca animacj� obiektu sprite na podstawie handlera bitmapy i obiektu gracza.
 * @param bitmap Handler bitmapy u�ywanej do animacji.
 * @param player Wska�nik do obiektu gracza, kt�rego animacja ma by� zmieniona.
 */
void Engine::SpriteObject::animate(BitmapHandler bitmap, Player* player) {
	player->setPlayerBitmap(bitmap);
}