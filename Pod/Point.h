#pragma once
#include <iostream>

class Point
{
private:
	int x, y;

public:
	// Init
	Point(int _x, int _y);

	// Getter
	int getX();
	int getY();

	// Setter
	void setX(int _x);
	void setY(int _y);

	// Overload operator
	bool operator == (const Point& point);
	friend std::ostream& operator<<(std::ostream& output, const Point& point) {
		output << "("
			<< point.x
			<< ", "
			<< point.y
			<< ")";

		return output;
	}

	friend std::ostream& operator<<(std::ostream& output, const Point* point) {
		output << "("
			<< point->x
			<< ", "
			<< point->y
			<< ")";

		return output;
	}
};