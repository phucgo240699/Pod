#pragma once
class Camera
{
private:
	int x, y, width, height;

public:
	// Init
	Camera(int _x, int _y, int _width, int _height);

	// De Init
	~Camera();

	// Getter
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// Setter
	void setX(int _x);
	void setY(int _y);
	void setWidth(int _width);
	void setHeight(int _height);
};

