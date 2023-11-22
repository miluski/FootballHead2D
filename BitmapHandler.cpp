#include "Engine.hpp"

using namespace Game;

/**
 * @brief Domyœlny konstruktor obiektu BitmapHandler.
 */
Engine::BitmapHandler::BitmapHandler()
{
}

/**
 * @brief Konstruktor obiektu BitmapHandler z plikiem graficznym.
 *
 * @param fileName Œcie¿ka do pliku graficznego.
 */
Engine::BitmapHandler::BitmapHandler(string fileName) {
	this->bitmap.loadFromFile(fileName);
	this->bitmap.setSmooth(true);
}

/**
 * @brief Konstruktor obiektu BitmapHandler z obiektem Text, rozmiarem i kolorem tekstury.
 *
 * @param text Obiekt Text reprezentuj¹cy tekst do umieszczenia na teksturze.
 * @param size Obiekt Vector2i reprezentuj¹cy rozmiar tekstury.
 * @param textureColor Kolor t³a tekstury.
 */
Engine::BitmapHandler::BitmapHandler(Text text, Vector2i size, Color textureColor) {
	RenderTexture renderTexture;
	renderTexture.create(size.x, size.y);
	renderTexture.clear(textureColor);
	renderTexture.draw(text);
	renderTexture.display();
	Texture bufferTexture(renderTexture.getTexture());
	this->bitmap.swap(bufferTexture);
}

/**
 * @brief Tworzy now¹ bitmapê o podanym rozmiarze.
 *
 * @param size Obiekt Vector2f reprezentuj¹cy rozmiar nowej bitmapy.
 */
void Engine::BitmapHandler::createBitmap(Vector2f size) {
	this->bitmap.create(size.x, size.y);
}

/**
 * @brief £aduje bitmapê z pliku o podanej œcie¿ce.
 *
 * @param fileName Œcie¿ka do pliku graficznego.
 */
void Engine::BitmapHandler::loadBitmapFrom(string fileName) {
	this->bitmap.loadFromFile(fileName);
	this->bitmap.setSmooth(true);
}

/**
 * @brief Tworzy bitmapê na podstawie obiektu Text, rozmiaru i koloru tekstury.
 *
 * @param text Obiekt Text reprezentuj¹cy tekst do umieszczenia na teksturze.
 * @param size Obiekt Vector2i reprezentuj¹cy rozmiar tekstury.
 * @param textureColor Kolor t³a tekstury.
 */
void Engine::BitmapHandler::createBitmapFrom(Text text, Vector2i size, Color textureColor) {
	RenderTexture renderTexture;
	renderTexture.create(size.x, size.y);
	renderTexture.clear(textureColor);
	renderTexture.draw(text);
	renderTexture.display();
	Texture bufferTexture(renderTexture.getTexture());
	this->bitmap.swap(bufferTexture);
}

/**
 * @brief Tworzy kopiê obiektu BitmapHandler.
 *
 * @return Nowy obiekt BitmapHandler bêd¹cy kopi¹ bie¿¹cego obiektu.
 */
Engine::BitmapHandler Engine::BitmapHandler::copy() {
	BitmapHandler bitmapHandler;
	Texture secondBitmap;
	Image bufferImage = this->bitmap.copyToImage();
	bufferImage.create(bufferImage.getSize().x, bufferImage.getSize().y);
	secondBitmap.update(bufferImage);
	bitmapHandler.setBitmap(secondBitmap);
	return bitmapHandler;
}

/**
 * @brief Zapisuje bitmapê do pliku o podanej œcie¿ce.
 *
 * @param fileName Œcie¿ka do pliku, w którym ma zostaæ zapisana bitmapa.
 */
void Engine::BitmapHandler::saveBitmapTo(string fileName) {
	Image image = this->bitmap.copyToImage();
	image.saveToFile(fileName);
}

/**
 * @brief Usuwa aktualn¹ bitmapê.
 */
void Engine::BitmapHandler::deleteBitmap() {
	this->bitmap.~Texture();
}

/**
 * @brief Ustawia bitmapê na podstawie podanej tekstury.
 *
 * @param bitmap Nowa tekstura do ustawienia jako bitmapa.
 */
void Engine::BitmapHandler::setBitmap(Texture bitmap) {
	this->bitmap.swap(bitmap);
}