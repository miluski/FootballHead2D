#include "Engine.hpp"

using namespace Game;

/**
 * @brief Rysuje prostok�t na ekranie o podanych wymiarach, pozycji i kolorze.
 *
 * @param size Wymiary prostok�ta.
 * @param position Pozycja prostok�ta.
 * @param color Kolor prostok�ta.
 */
void PrimitiveRenderer::drawRectangle(Vector2f size, Vector2f position, Color color) {
	Engine::Rectangle rectangle(size);
	rectangle.setColor(color);
	rectangle.translate(position);
	rectangle.draw();
}

/**
 * @brief Rysuje ko�o na ekranie o podanym promieniu, pozycji i kolorze.
 *
 * @param radius Promie� ko�a.
 * @param position Pozycja ko�a.
 * @param color Kolor ko�a.
 */
void PrimitiveRenderer::drawCircle(float radius, Vector2f position, Color color) {
	Engine::Circle circle(radius);
	circle.setColor(color);
	circle.translate(position);
	circle.draw();
}

/**
 * @brief Rysuje symetryczne ko�o na ekranie o podanym promieniu, punkcie pocz�tkowym i kolorze.
 *
 * @param radius Promie� ko�a.
 * @param startPoint Punkt pocz�tkowy ko�a.
 * @param color Kolor ko�a.
 */
void PrimitiveRenderer::drawSymetricCircle(float radius, Point2D startPoint, Color color) {
	for (float i = 0.0f; i < 180.0f; i += 1.0f) {
		float x = radius * cos(i);
		float y = radius * sin(i);
		Vertex point(Vector2f(startPoint.getX() + x, startPoint.getY() + y), color);
		Engine::getInstance().getMainWindow()->draw(&point, 1, Points);
		Vertex point2(Vector2f(startPoint.getX() + x, startPoint.getY() - y), color);
		Engine::getInstance().getMainWindow()->draw(&point2, 1, Points);
		Vertex point3(Vector2f(startPoint.getX() - x, startPoint.getY() + y), color);
		Engine::getInstance().getMainWindow()->draw(&point3, 1, Points);
		Vertex point4(Vector2f(startPoint.getX() - x, startPoint.getY() - y), color);
		Engine::getInstance().getMainWindow()->draw(&point4, 1, Points);
	}
}

/**
 * @brief Rysuje tr�jk�t na ekranie o podanym rozmiarze, pozycji i kolorze.
 *
 * @param radius Promie� tr�jk�ta.
 * @param position Pozycja tr�jk�ta.
 * @param color Kolor tr�jk�ta.
 */
void PrimitiveRenderer::drawTriangle(float radius, Vector2f position, Color color) {
	Engine::Triangle triangle(radius);
	triangle.setColor(color);
	triangle.translate(position);
	triangle.draw();
}

/**
 * @brief Rysuje zwi�kszon� lini� mi�dzy dwoma punktami na ekranie o podanym kolorze.
 *
 * @param startCoords Wsp�rz�dne pocz�tkowe linii.
 * @param endCoords Wsp�rz�dne ko�cowe linii.
 * @param color Kolor linii.
 */
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
	Engine::getInstance().getMainWindow()->draw(pointsArray);
}

/**
 * @brief Rysuje lini� mi�dzy dwoma punktami na ekranie o podanym kolorze.
 *
 * @param startCoords Wsp�rz�dne pocz�tkowe linii.
 * @param endCoords Wsp�rz�dne ko�cowe linii.
 * @param color Kolor linii.
 */
void PrimitiveRenderer::drawLine(Vector2f startCoords, Vector2f endCoords, Color color) {
	Vertex line[] =
	{
		Vertex(Vector2f(startCoords.x, startCoords.y), color),
		Vertex(Vector2f(endCoords.x, endCoords.y), color)
	};
	Engine::getInstance().getMainWindow()->draw(line, 2, Lines);
}

/**
 * @brief Rysowanie linii �amanej na ekranie, sk�adaj�cej si� z podanych odcink�w i koloru.
 *
 * @param lines Wektor zawieraj�cy odcinki linii �amanej.
 * @param color Kolor linii �amanej.
 */
void PrimitiveRenderer::drawBrokenLine(vector<LineSegment> lines, Color color) {
	for (LineSegment line : lines) {
		Vertex lineVertex[] = {
			Vertex(Vector2f(line.getStartPoint().getX(), line.getStartPoint().getY()), color, Vector2f(5.0f, 0.0f)),
			Vertex(Vector2f(line.getEndPoint().getX(), line.getEndPoint().getY()), color, Vector2f(5.0f, 0.0f))
		};
		Engine::getInstance().getMainWindow()->draw(lineVertex, 2, Lines);
	}
}

/**
 * @brief Rysuje elips� na ekranie o podanych promieniach, punkcie pocz�tkowym i kolorze.
 *
 * @param radiusX Promie� X elipsy.
 * @param radiusY Promie� Y elipsy.
 * @param startPoint Punkt pocz�tkowy elipsy.
 * @param color Kolor elipsy.
 */
void PrimitiveRenderer::drawEllipse(float radiusX, float radiusY, Point2D startPoint, Color color) {
	for (float i = 0.0f; i < 180.0f; i += 1.0f) {
		float x = radiusX * cos(i);
		float y = radiusY * sin(i);
		Vertex point(Vector2f(startPoint.getX() + x, startPoint.getY() + y), color);
		Engine::getInstance().getMainWindow()->draw(&point, 1, Points);
		Vertex point2(Vector2f(startPoint.getX() + x, startPoint.getY() - y), color);
		Engine::getInstance().getMainWindow()->draw(&point2, 1, Points);
		Vertex point3(Vector2f(startPoint.getX() - x, startPoint.getY() + y), color);
		Engine::getInstance().getMainWindow()->draw(&point3, 1, Points);
		Vertex point4(Vector2f(startPoint.getX() - x, startPoint.getY() - y), color);
		Engine::getInstance().getMainWindow()->draw(&point4, 1, Points);
	}
}

/**
 * @brief Sprawdza, czy dwie linie przecinaj� si�.
 *
 * @param line1 Pierwszy odcinek.
 * @param line2 Drugi odcinek.
 * @return Warto�� logiczna informuj�ca o przeci�ciu si� linii.
 */
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

/**
 * @brief Rysuje wielok�t na ekranie o podanych odcinkach i kolorze.
 *
 * @param lines Wektor zawieraj�cy odcinki wielok�ta.
 * @param color Kolor wielok�ta.
 */
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
		Engine::getInstance().getMainWindow()->draw(lineVertex, 2, Lines);
	}
}


/**
 * @brief Rysuje wype�niony obszar prostok�tny, zaczynaj�c od punktu o podanym kolorze wype�nienia i obramowaniem.
 *
 * @param point Punkt startowy rysowania.
 * @param fillColor Kolor wype�nienia obszaru.
 * @param borderColor Kolor obramowania obszaru.
 */
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

/**
 * @brief Algorytm wype�niania obszaru prostok�tnego.
 *
 * Funkcja wype�nia obszar prostok�tny, zaczynaj�c od danego punktu, okre�lonym kolorem wype�nienia.
 * Zachowuje granice obszaru oraz omija obszary o tle r�wnym kolorowi t�a lub przezroczystemu.
 *
 * Algorytm wykorzystuje podej�cie oparte na kolejce do efektywnego przeszukiwania i wype�niania obszaru.
 *
 * @param point Pocz�tkowy punkt dla operacji wype�niania obszaru.
 * @param fillColor Kolor u�ywany do wype�nienia obszaru.
 * @param backgroundColor Kolor traktowany jako t�o, kt�re nie jest wype�niane.
 *
 * @see Point2D, Color
 */
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