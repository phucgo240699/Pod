#include "Camera.h"

//Camera::Camera(float _x, float _y, float _width, float _height) : Component(_x, _y)
//{
//	Component::Component(_x, _y);
//	this->width = _width;
//	this->height = _height;
//}
//
//Camera::Camera(D3DXVECTOR3* _position, float _width, float _height) : Component(_position)
//{
//	Component::Component(_position);
//	this->width = _width;
//	this->height = _height;
//}
//
//Camera::Camera(RECT r) : Component(r.left, r.top)
//{
//	if (r.right < r.left) {
//		throw "Right anchor must be greater than left anchor";
//	}
//	if (r.right < r.left) {
//		throw "Bottom anchor must be greater than top anchor";
//	}
//	Component::Component(r.left, r.top);
//	this->width = r.right - r.left;
//	this->height = r.top - r.bottom;
//}

Camera* Camera::instance;

Camera::Camera(float _x, float _y) : Component(_x, _y)
{
	Component::Component(_x, _y);
	this->width = Setting::getInstance()->getScreenWidth();
	this->height = Setting::getInstance()->getScreenHeight();
}

Camera* Camera::getInstance()
{
	if (instance == nullptr) {
		instance = new Camera(0, 0);
	}
	return instance;
}

float Camera::getWidth()
{
	return this->width;
}

float Camera::getHeight()
{
	return this->height;
}

void Camera::setWidth(float _width)
{
	this->width = _width;
}

void Camera::setHeight(float _height)
{
	this->height = _height;
}

void Camera::load()
{
	// Read data from file
	string data = FileManager::getInstance()->getStringFromTextFile("camera.txt");
	vector<string> v = Tool::splitToVectorStringFrom(data, ',');

	if (v.size() == 2) {
		instance = new Camera(stoi(v[0]), stoi(v[1]));
		instance->width = Setting::getInstance()->getScreenWidth();
		instance->height = Setting::getInstance()->getScreenHeight();
	}
}

void Camera::save()
{
	string data = "";
	data += to_string(instance->position->x);
	data += ",";
	data += to_string(instance->position->y);
	FileManager::getInstance()->writeStringToTextFile("camera.txt", data);
}

