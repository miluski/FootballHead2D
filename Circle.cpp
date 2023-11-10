#include "Engine.hpp"

void Circle::draw() {
	CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(getX(), getY());
	mainWindow->draw(circle);
}
void Circle::translate() {

}
void Circle::rotate() {

}
void Circle::scale() {

}