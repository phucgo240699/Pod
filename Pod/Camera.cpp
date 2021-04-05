#include "Camera.h"

Camera* Camera::instance;

Camera::Camera(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, limitY)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, limitY);
	this->width = Setting::getInstance()->getScreenWidth();
	this->height = Setting::getInstance()->getScreenHeight();
}

Camera* Camera::getInstance()
{
	if (instance == nullptr) {
		instance = new Camera(0, 0, 0, 0, 0, 0);
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

//void Camera::followRECT(RECT* _targetRect, float _vx, float _vy, float _dt)
//{
//	// Target rect is RECT object that camera need to follow
//	if (_targetRect->right < _targetRect->left) {
//		throw "Right anchor must be greater than or equal left anchor";
//	}
//	if (_targetRect->bottom < _targetRect->top) {
//		throw "Bottom anchor must be greater than or equal top anchor";
//	}
//
//	float targetWidth = _targetRect->right - _targetRect->left;
//	float targetHeight = _targetRect->bottom - _targetRect->top;
//	bool isTargetInHorizontalSafeArea = false;
//	bool isTargetInVertialSafeArea = false;
//	this->vx = _vx;
//	this->vy = _vy;	
//	this->dt = _dt;
//	float dx = this->vx * this->dt;
//	float dy = this->vy * this->dt;
//
//	if (this->getX() + dx >= 0 && this->getX() + this->width + dx <= this->limitX) {
//		this->plusX(this->vx * this->dt);
//	}
//	if (this->getY() + dy >= 0 && this->getY() + this->height + dy <= this->limitY) {
//		this->plusY(this->vy * this->dt);
//	}
//}

void Camera::load()
{
	// Read data from camera file
	string data = FileManager::getInstance()->getStringFromTextFile("camera.txt");
	vector<int> v = Tool::splitToVectorIntegerFrom(data, ',');

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);

	// Read data from map file
	data = FileManager::getInstance()->getStringFromTextFile("map_info_man1.txt");
	v = Tool::splitToVectorIntegerFrom(data, ',');
	this->setLimitX(v[4]);
	this->setLimitY(v[5]);
}

void Camera::save()
{
	string data = "";
	data += to_string(this->position->x);
	data += ",";
	data += to_string(this->position->y);
	data += ",";
	data += to_string(this->vx);
	data += ",";
	data += to_string(this->vy);
	data += ",";
	data += to_string(this->limitX);
	data += ",";
	data += to_string(this->limitY);
	FileManager::getInstance()->writeStringToTextFile("camera.txt", data);
}

