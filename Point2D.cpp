#include "Engine.hpp"

Point2D::Point2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Point2D::Point2D(Color pixelColor, float x, float y) {
	this->pixelColor = pixelColor;
	this->x = x;
	this->y = y;
}

float Point2D::getX() {
	return this->x;
}

float Point2D::getY() {
	return this->y;
}

Color Point2D::getPixelColor() {
	RenderWindow* mainWindow = Engine::getInstance().getMainWindow();
	if ((this->getX() < mainWindow->getSize().x) && (this->getY() < mainWindow->getSize().y)) {
		Texture mainWindowTexture;
		mainWindowTexture.create(mainWindow->getSize().x, mainWindow->getSize().y);
		mainWindowTexture.update(*mainWindow);
		Image mainWindowImage = mainWindowTexture.copyToImage();
		Color pixelColor = mainWindowImage.getPixel(this->getX(), this->getY());
		setPixelColor(pixelColor);
		return pixelColor;
	}
	else
		return Color::Transparent;
}

void Point2D::setPixelColor(Color pixelColor) {
	this->pixelColor = pixelColor;
}

void Point2D::setCoords(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point2D::draw() {
	PrimitiveRenderer primitiveRenderer;
	primitiveRenderer.drawCircle(1.0f, Vector2f(this->x, this->y), pixelColor);
}