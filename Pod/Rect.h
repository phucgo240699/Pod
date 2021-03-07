#pragma once
#include "Point.h"
#include "Size.h"
#include <d3d9.h>


class Rect {
private:
	Point* location;
	Size* size;

public:

	// Init
	Rect(Point* _location, Size* _size);
	Rect(int _x, int _y, int _width, int _height);

	// De-Init
	~Rect();

	// Getter
	Point* getLocation();
	Size* getSize();

	// Setter
	void setLocation(Point* _location);
	void setSize(Size* _size);

	// Anchors
	int getTopAnchor();
	int getBottomAnchor();
	int getLeftAnchor();
	int getRightAnchor();

	// Dectection
	bool isIntersect(Rect anotherRect);
	bool isContain(Rect anotherRect);


	RECT toRECTForD3D();


	// Overload operators
	bool operator == (const Rect& rect) {
		if (this->location == rect.location && this->size == rect.size) {
			return true;
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream& output, const Rect& rect) {
		output << "("
			<< rect.location->getX()
			<< ", "
			<< rect.location->getY()
			<< ", "
			<< rect.size->getWidth()
			<< ", "
			<< rect.size->getHeight()
			<< ")";

		return output;
	}
	friend std::ostream& operator<<(std::ostream& output, const Rect * rect) {
		output << "("
			<< rect->location->getX()
			<< ", "
			<< rect->location->getY()
			<< ", "
			<< rect->size->getWidth()
			<< ", "
			<< rect->size->getHeight()
			<< ")";

		return output;
	}

};