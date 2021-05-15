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

void Camera::setPositionBy(Component* _target)
{
	/*float newX = _target->getX() - (this->getWidth() / 2);
	float newY = newY = _target->getY() - (this->getHeight() / 2);;
	if (newX < 0) {
		newX = 0;
	}
	else if (newX + this->getWidth() > this->getLimitX()) {
		newX = this->getLimitX() - this->getWidth();
	}

	if (newY < 0) {
		newY = 0;
	}
	else if (newY + this->getHeight() > this->getLimitY()) {
		newY = this->getLimitY() - this->getHeight();
	}

	this->setX(newX);
	this->setY(newY);*/

	if (_target->getX() <= this->getWidth() / 2) {
		this->setX(0);
	}
	else if (_target->getX() > this->getLimitX() - (this->getWidth() / 2)) {
		this->setX(this->getLimitX() - this->getWidth());
	}
	else {
		this->setX(_target->getX() - (this->getWidth() / 2));
	}

	if (_target->getY() <= this->getHeight() / 2) {
		this->setY(0);
	}
	else if (_target->getY() > this->getLimitY() - (this->getHeight() / 2)) {
		this->setY(this->getLimitY() - this->getHeight());
	}
	else {
		this->setY(_target->getY() - (this->getHeight() / 2));
	}
}

void Camera::follow(Component* _target, float _dt)
{
	// If target not in safe area, and new location of camera not outside of map
	if (_target->getX() > this->getWidth() / 2 &&
		_target->getX() < this->getLimitX() - (this->getWidth() / 2) &&
		0 < this->getX() + _target->getCurrentVx() &&
		this->getX() + this->getWidth() + _target->getCurrentVx() < this->getLimitX()) {
		this->plusX(_target->getCurrentVx());
	}

	// If target run through half of camera's height, and new location of camera not outside of map
	if (_target->getY() > this->getHeight() / 2 &&
		_target->getY() < this->getLimitY() - (this->getHeight() / 2) &&
		0 < this->getY() + _target->getCurrentVy() &&
		this->getY() + this->getHeight() + _target->getCurrentVy() < this->getLimitY()) {
		this->plusY(_target->getCurrentVy());
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

