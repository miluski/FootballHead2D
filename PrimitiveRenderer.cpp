#include "Engine.hpp"

RenderWindow* mainWindow = Engine::getInstance().getMainWindow();

void PrimitiveRenderer::drawRectangle(Vector2f size, Vector2f position, Color color) {
	RectangleShape rectangle(size);
	rectangle.setFillColor(color);
	rectangle.setPosition(position);
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(rectangle);
}

void PrimitiveRenderer::drawCircle(float radius, Vector2f position, Color color) {
	CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(position);
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(circle);
}

void PrimitiveRenderer::drawTriangle(float radius, Vector2f position, Color color) {
	CircleShape triangle(radius, 3);
	triangle.setFillColor(color);
	triangle.setPosition(position);
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(triangle);
}

void PrimitiveRenderer::drawIncreasedLine(Vector2f startCoords, Vector2f endCoords, Color color) {
	VertexArray pointsArray(Points);
	float dy = endCoords.y - startCoords.y;
	float dx = endCoords.x - startCoords.x;
	float m = dy / dx;
	if (abs(m) <= 1) {
		float y = startCoords.y;
		for (int x = startCoords.x; x <= endCoords.x; x++) {
			Vector2f linePointCoords(x, y);
			Vertex linePointVertex(linePointCoords, color);
			pointsArray.append(linePointVertex);
			y += m;
		}
	}
	else {
		m = dx / dy;
		float x = startCoords.x;
		for (int y = startCoords.y; y <= endCoords.y; y++) {
			Vector2f linePointCoords(x, y);
			Vertex linePointVertex(linePointCoords, color);
			pointsArray.append(linePointVertex);
			x += m;
		}
	}
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(pointsArray);
}

void PrimitiveRenderer::drawLine(Vector2f startCoords, Vector2f endCoords, Color color) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(startCoords.x, startCoords.y)),
		sf::Vertex(sf::Vector2f(endCoords.x, endCoords.y))
	};
	line->color = color;
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(line, 2, sf::Lines);
}