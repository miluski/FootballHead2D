#include "Engine.hpp"

void Triangle::draw() {
	CircleShape triangle(radius, 3);
	triangle.setFillColor(color);
	triangle.setPosition(getX(), getY());
	mainWindow->draw(triangle);
}
void Triangle::translate() {

}
void Triangle::rotate() {

}
void Triangle::scale() {

}