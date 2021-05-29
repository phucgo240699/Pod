#pragma once
#include "Component.h";

class Ground : public Component
{
private:
	float width, height;

public:
	Ground(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY);
	Ground(D3DXVECTOR3* _position, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY);

	~Ground();


	// Inherit
	float getWidth();
	float getHeight();
	RECT* getBounds();
	void setWidth(float _width);
	void setHeight(float _height);

	void load(string line, char seperator);
};

