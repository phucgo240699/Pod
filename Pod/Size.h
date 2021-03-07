#pragma once
#include <iostream>

class Size {
private:
	int width, height;

public:
	// Init
	Size(int _width, int _height);

	// Getter
	int getWidth();
	int getHeight();

	// Setter
	void setWidth(int _width);
	void setHeight(int _height);

	// Overload operator
	bool operator == (const Size& size);
	friend std::ostream& operator<<(std::ostream& output, const Size& size) {
		output << "("
			<< size.width
			<< ", "
			<< size.height
			<< ")";

		return output;
	}

	friend std::ostream& operator<<(std::ostream& output, const Size * size) {
		output << "("
			<< size->width
			<< ", "
			<< size->height
			<< ")";

		return output;
	}
};