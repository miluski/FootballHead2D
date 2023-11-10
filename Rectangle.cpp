#include "Engine.hpp"

void Rectangle::draw() {
	RectangleShape rectangle(size);
	rectangle.setFillColor(color);
	rectangle.setPosition(getX(), getY());
	mainWindow->draw(rectangle);
}
void Rectangle::translate() {

}
void Rectangle::rotate() {

}
void Rectangle::scale() {

}