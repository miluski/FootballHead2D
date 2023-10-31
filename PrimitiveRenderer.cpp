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

void PrimitiveRenderer::drawSymetricCircle(float radius, Point2D startPoint, Color color) {
	// Czterokrotna symetria
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	for (float i = 0.0f; i < 180.0f; i += 1.0f) {
		float x = radius * cos(i);
		float y = radius * sin(i);
		Vertex point(Vector2f(startPoint.getX() + x, startPoint.getY() + y), color);
		mainWindow->draw(&point, 1, Points);
		Vertex point2(Vector2f(startPoint.getX() + x, startPoint.getY() - y), color);
		mainWindow->draw(&point2, 1, Points);
		Vertex point3(Vector2f(startPoint.getX() - x, startPoint.getY() + y), color);
		mainWindow->draw(&point3, 1, Points);
		Vertex point4(Vector2f(startPoint.getX() - x, startPoint.getY() - y), color);
		mainWindow->draw(&point4, 1, Points);
	}
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
	Vertex line[] =
	{
		Vertex(Vector2f(startCoords.x, startCoords.y)),
		Vertex(Vector2f(endCoords.x, endCoords.y))
	};
	line->color = color;
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	mainWindow->draw(line, 2, Lines);
}

void PrimitiveRenderer::drawBrokenLine(vector<LineSegment> lines, Color color) {
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	for (LineSegment line : lines) {
		Vertex lineVertex[] = {
			Vertex(Vector2f(line.getStartPoint().getX(), line.getStartPoint().getY())),
			Vertex(Vector2f(line.getEndPoint().getX(), line.getEndPoint().getY()))
		};
		lineVertex->color = color;
		mainWindow->draw(lineVertex, 2, Lines);
	}
}

void PrimitiveRenderer::drawEllipse(float radiusX, float radiusY, Point2D startPoint, Color color) {
	// Czterokrotna symetria
	Engine::getInstance().clearWindowToColor(Color(58, 157, 35));
	for (float i = 0.0f; i < 180.0f; i += 1.0f) {
		float x = radiusX * cos(i);
		float y = radiusY * sin(i);
		Vertex point(Vector2f(startPoint.getX() + x, startPoint.getY() + y), color);
		mainWindow->draw(&point, 1, Points);
		Vertex point2(Vector2f(startPoint.getX() + x, startPoint.getY() - y), color);
		mainWindow->draw(&point2, 1, Points);
		Vertex point3(Vector2f(startPoint.getX() - x, startPoint.getY() + y), color);
		mainWindow->draw(&point3, 1, Points);
		Vertex point4(Vector2f(startPoint.getX() - x, startPoint.getY() - y), color);
		mainWindow->draw(&point4, 1, Points);
	}
}

void PrimitiveRenderer::drawPolygon(vector<LineSegment> lines, Color color) {

}