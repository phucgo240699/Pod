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

bool Camera::getOnTopSafeArea()
{
	return this->onTopSafeArea;
}

bool Camera::getOnBottomSafeArea()
{
	return this->onBottomSafeArea;
}

bool Camera::getOnLeftSafeArea()
{
	return this->onLeftSafeArea;
}

bool Camera::getOnRightSafeArea()
{
	return this->onRightSafeArea;
}

void Camera::setWidth(float _width)
{
	this->width = _width;
}

void Camera::setHeight(float _height)
{
	this->height = _height;
}

void Camera::followRECT(RECT* _targetRect, float _vx, float _vy, float _dt)
{
	if (_targetRect == NULL) {
		return;
	}
	// Target rect is RECT object that camera need to follow
	if (_targetRect->right < _targetRect->left) {
		throw "Right anchor must be greater than or equal left anchor";
	}
	if (_targetRect->bottom < _targetRect->top) {
		throw "Bottom anchor must be greater than or equal top anchor";
	}
	
	float targetWidth = _targetRect->right - _targetRect->left;
	float targetHeight = _targetRect->bottom - _targetRect->top;

	// Vertical SafeArea
	if (_targetRect->left + (targetWidth / 2) <= this->width / 2) {
		this->setX(0);
		this->onLeftSafeArea = true;
		this->onRightSafeArea = false;
	}
	else if (_targetRect->left + (targetWidth / 2) >= this->limitX - (this->width / 2)) {
		this->setX(this->limitX - this->width);
		this->onLeftSafeArea = false;
		this->onRightSafeArea = true;
	}
	else {
		this->setX(_targetRect->left - ((this->width / 2) - (targetWidth / 2)));
		this->onLeftSafeArea = false;
		this->onRightSafeArea = false;
	}

	// Horizontal SafeArea
	if (_targetRect->top + (targetHeight / 2) <= this->height / 2) {
		this->setY(0);
		this->onTopSafeArea = true;
		this->onBottomSafeArea = false;
	}
	else if (_targetRect->top + (targetHeight / 2) >= this->limitY - (this->height / 2)) {
		this->setY(this->limitY - this->height);
		this->onTopSafeArea = false;
		this->onBottomSafeArea = true;
	}
	else {
		this->setY(_targetRect->top - ((this->height / 2) - (targetHeight / 2)));
		this->onTopSafeArea = false;
		this->onBottomSafeArea = false;
	}
}

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

	// Validate data
	if (this->getX() + this->width > this->limitX) {
		throw("Camera is out side of map by X-axis.");
	}
	if (this->getY() + this->height > this->limitY) {
		throw("Camera is out side of map by Y-axis.");
	}
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

