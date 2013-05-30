#ifndef RECT_HPP
#define RECT_HPP

#include <Vector2.hpp>

class Rect
{
public:
	Rect() { Set(0, 0, 0, 0); }
	Rect(Vector2 p1, Vector2 p2) { Set(p1, p2); }
	Rect(float x1, float y1, float x2, float y2) { Set(x1, y1, x2, y2); }
	~Rect() {};

	void Set(Vector2 p1, Vector2 p2)
	{
		Point1 = p1;
		Point2 = p2;
	}

	void Set(float x1, float y1, float x2, float y2)
	{
		Point1.x = x1; Point1.y = y1;
		Point2.x = x2; Point2.y = y2;
	}

	Vector2 GetStart() { return Point1; }
	Vector2 GetEnd() { return Point2; }

	bool Intersect(Rect other)
	{
		if (IsInside(other.Point1.x, other.Point1.y)) return true;
		if (IsInside(other.Point2.x, other.Point1.y)) return true;
		if (IsInside(other.Point1.x, other.Point2.y)) return true;
		if (IsInside(other.Point2.x, other.Point2.y)) return true;

		return false;
	}

	bool IsInside(Vector2 point)
	{
		return IsInside(point.x, point.y);
	}

	bool IsInside(float x, float y)
	{
		return (x >= Point1.x && x <= Point2.x && y >= Point1.y && y <= Point2.y);
	}

private:
	Vector2 Point1, Point2;
};

#endif