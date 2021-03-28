#pragma once
#include "Component.h"
#include <d3d9.h>


class Camera : public Component
{
private:
	float width, height;
public:
	// Init
	Camera(float _x, float _y, float _width, float _height);
	Camera(D3DXVECTOR3* _position, float _width, float _height);
	Camera(RECT r);

	// Getter
	float getWidth();
	float getHeight();

	// Setter
	void setWidth(float _width);
	void setHeight(float _height);
};

