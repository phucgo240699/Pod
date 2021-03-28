#include "Camera.h"

Camera::Camera(float _x, float _y, float _width, float _height) : Component(_x, _y)
{
	Component::Component(_x, _y);
	this->width = _width;
	this->height = _height;
}

Camera::Camera(D3DXVECTOR3* _position, float _width, float _height) : Component(_position)
{
	Component::Component(_position);
	this->width = _width;
	this->height = _height;
}

Camera::Camera(RECT r) : Component(r.left, r.top)
{
	if (r.right < r.left) {
		throw "Right anchor must be greater than left anchor";
	}
	if (r.right < r.left) {
		throw "Bottom anchor must be greater than top anchor";
	}
	Component::Component(r.left, r.top);
	this->width = r.right - r.left;
	this->height = r.top - r.bottom;
}

