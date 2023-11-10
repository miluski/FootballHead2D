#include "Engine.hpp"

void PrimitiveRenderer::drawRectangle(Vector2f size, Vector2f position, Color color) {
	RectangleShape rectangle(size);
	rectangle.setFillColor(color);
	rectangle.setPosition(position);
	mainWindow->draw(rectangle);
}

void PrimitiveRenderer::drawCircle(float radius, Vector2f position, Color color) {
	CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(position);
	mainWindow->draw(circle);
}

void PrimitiveRenderer::drawSymetricCircle(float radius, Point2D startPoint, Color color) {
	// Czterokrotna symetria
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
	mainWindow->draw(triangle);
}

void PrimitiveRenderer::drawIncreasedLine(Vector2f startCoords, Vector2f endCoords, Color color) {
	VertexArray pointsArray(Points);
	float dy = endCoords.y - startCoords.y;
	float dx = endCoords.x - startCoords.x;
	float m = dy / dx;
	if (abs(m) <= 1) {
		float y = startCoords.y;
		for (float x = startCoords.x; x <= endCoords.x; x++) {
			Vector2f linePointCoords(x, y);
			Vertex linePointVertex(linePointCoords, color, Vector2f(5.0f, 0.0f));
			pointsArray.append(linePointVertex);
			y += m;
		}
	}
	else {
		m = dx / dy;
		float x = startCoords.x;
		for (float y = startCoords.y; y <= endCoords.y; y++) {
			Vector2f linePointCoords(x, y);
			Vertex linePointVertex(linePointCoords, color, Vector2f(5.0f, 0.0f));
			pointsArray.append(linePointVertex);
			x += m;
		}
	}
	mainWindow->draw(pointsArray);
}

void PrimitiveRenderer::drawLine(Vector2f startCoords, Vector2f endCoords, Color color) {
	Vertex line[] =
	{
		Vertex(Vector2f(startCoords.x, startCoords.y), color),
		Vertex(Vector2f(endCoords.x, endCoords.y), color)
	};
	mainWindow->draw(line, 2, Lines);
}

void PrimitiveRenderer::drawBrokenLine(vector<LineSegment> lines, Color color) {
	for (LineSegment line : lines) {
		Vertex lineVertex[] = {
			Vertex(Vector2f(line.getStartPoint().getX(), line.getStartPoint().getY()), color, Vector2f(5.0f, 0.0f)),
			Vertex(Vector2f(line.getEndPoint().getX(), line.getEndPoint().getY()), color, Vector2f(5.0f, 0.0f))
		};
		mainWindow->draw(lineVertex, 2, Lines);
	}
}

void PrimitiveRenderer::drawEllipse(float radiusX, float radiusY, Point2D startPoint, Color color) {
	// Czterokrotna symetria
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

bool PrimitiveRenderer::isLinesCrossing(LineSegment line1, LineSegment line2) {
	Point2D line1StartPoint = line1.getStartPoint();
	Point2D line2StartPoint = line2.getStartPoint();
	Point2D line1EndPoint = line1.getEndPoint();
	Point2D line2EndPoint = line2.getEndPoint();
	float dx1 = line1EndPoint.getX() - line1StartPoint.getX();
	float dx2 = line2EndPoint.getX() - line2StartPoint.getX();
	float dy1 = line1EndPoint.getY() - line1StartPoint.getY();
	float dy2 = line2EndPoint.getY() - line2StartPoint.getY();
	float cross = dx1 * dy2 - dx2 * dy1;
	if (cross == 0)
		return false;
	else {
		float crossX = (((line2StartPoint.getX() - line1StartPoint.getX()) * dy2 -
			(line2StartPoint.getY() - line1StartPoint.getY()) * dx2) / cross);
		float crossY = (((line2StartPoint.getX() - line1StartPoint.getX()) * dy1 -
			(line2StartPoint.getY() - line1StartPoint.getY()) * dx1) / cross);
		if (crossX > 0 && crossX < 1 && crossY > 0 && crossY < 1)
			return true;
	}
	return false;
}

void PrimitiveRenderer::drawPolygon(vector<LineSegment> lines, Color color) {
	for (int i = 0; i < lines.size(); i++) {
		for (int j = i + 1; j < lines.size(); j++) {
			if (isLinesCrossing(lines[i], lines[j]) || j > lines.size())
				return;
		}
	}
	for (LineSegment line : lines) {
		Vertex lineVertex[] = {
			Vertex(Vector2f(line.getStartPoint().getX(), line.getStartPoint().getY()), color),
			Vertex(Vector2f(line.getEndPoint().getX(), line.getEndPoint().getY()), color)
		};
		mainWindow->draw(lineVertex, 2, Lines);
	}
}

void PrimitiveRenderer::borderRectFill(Point2D point, Color fillColor, Color borderColor) {
	queue<Point2D> pixelQueue;
	pixelQueue.push(point);
	while (!pixelQueue.empty()) {
		point = pixelQueue.front();
		pixelQueue.pop();
		Color pixelColor = point.getPixelColor();
		if (pixelColor == fillColor || pixelColor == borderColor)
			continue;
		drawCircle(1.0f, Vector2f(point.getX(), point.getY()), fillColor);
		float pointX = point.getX();
		float pointY = point.getY();
		Point2D pointN(pointX, pointY + 1.0f);
		Point2D pointS(pointX, pointY - 1.0f);
		Point2D pointW(pointX - 1.0f, pointY);
		Point2D pointE(pointX + 1.0f, pointY);
		pixelQueue.push(pointN);
		pixelQueue.push(pointS);
		pixelQueue.push(pointW);
		pixelQueue.push(pointE);
	}
}

void PrimitiveRenderer::floodRectFill(Point2D point, Color fillColor, Color backgroundColor) {
	queue<Point2D> pixelQueue;
	pixelQueue.push(point);
	while (!pixelQueue.empty()) {
		point = pixelQueue.front();
		pixelQueue.pop();
		if (point.getPixelColor() == fillColor || point.getPixelColor() != backgroundColor || point.getPixelColor() == Color::Transparent)
			continue;
		point.setPixelColor(fillColor);
		point.draw();
		float pointX = point.getX();
		float pointY = point.getY();
		Point2D pointN(pointX, pointY + 1.0f);
		Point2D pointS(pointX, pointY - 1.0f);
		Point2D pointW(pointX - 1.0f, pointY);
		Point2D pointE(pointX + 1.0f, pointY);
		pixelQueue.push(pointN);
		pixelQueue.push(pointS);
		pixelQueue.push(pointW);
		pixelQueue.push(pointE);
	}
}