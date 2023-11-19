#include "Engine.hpp"

using namespace Game;

Engine::BitmapHandler::BitmapHandler()
{
}

Engine::BitmapHandler::BitmapHandler(string fileName) {
	this->bitmap.loadFromFile(fileName);
	this->bitmap.setSmooth(true);
}

Engine::BitmapHandler::BitmapHandler(Text text, Vector2i size, Color textureColor) {
	RenderTexture renderTexture;
	renderTexture.create(size.x, size.y);
	renderTexture.clear(textureColor);
	renderTexture.draw(text);
	renderTexture.display();
	Texture bufferTexture(renderTexture.getTexture());
	this->bitmap.swap(bufferTexture);
}

void Engine::BitmapHandler::createBitmap(Vector2f size) {
	this->bitmap.create(size.x, size.y);
}

void Engine::BitmapHandler::loadBitmapFrom(string fileName) {
	this->bitmap.loadFromFile(fileName);
	this->bitmap.setSmooth(true);
}

void Engine::BitmapHandler::createBitmapFrom(Text text, Vector2i size, Color textureColor) {
	RenderTexture renderTexture;
	renderTexture.create(size.x, size.y);
	renderTexture.clear(textureColor);
	renderTexture.draw(text);
	renderTexture.display();
	Texture bufferTexture(renderTexture.getTexture());
	this->bitmap.swap(bufferTexture);
}

Engine::BitmapHandler Engine::BitmapHandler::copy() {
	BitmapHandler bitmapHandler;
	Texture secondBitmap;
	Image bufferImage = this->bitmap.copyToImage();
	bufferImage.create(bufferImage.getSize().x, bufferImage.getSize().y);
	secondBitmap.update(bufferImage);
	bitmapHandler.setBitmap(secondBitmap);
	return bitmapHandler;
}

void Engine::BitmapHandler::saveBitmapTo(string fileName) {
	Image image = this->bitmap.copyToImage();
	image.saveToFile(fileName);
}

void Engine::BitmapHandler::deleteBitmap() {
	this->bitmap.~Texture();
}

void Engine::BitmapHandler::setBitmap(Texture bitmap) {
	this->bitmap.swap(bitmap);
}