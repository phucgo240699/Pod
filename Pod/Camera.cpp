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

void Camera::setPositionBy(Component* _target)
{
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
	// still have problem
	// If target not in safe area, and new location of camera not outside of map
	if (_target->getX() > this->getWidth() / 2 &&
		_target->getX() < this->getLimitX() - (this->getWidth() / 2) &&
		0 <= this->getX() + _target->getVx() &&
		this->getX() + this->getWidth() + _target->getVx() <= this->getLimitX()) {
		if ((_target->getVx() * _dt) > _target->getX() - (this->getWidth() / 2)) { // may cause when target move too fast
			this->plusX(_target->getX() - (this->getWidth() / 2));
		}
		else {
			//this->plusX(_target->getVx() * _dt);
			this->setX(_target->getX() - (this->getWidth() / 2));
		}
	}

	// If target run through half of camera's height, and new location of camera not outside of map
	if (_target->getY() > this->getHeight() / 2 &&
		_target->getY() < this->getLimitY() - (this->getHeight() / 2) &&
		0 <= this->getY() + _target->getVy() &&
		this->getY() + this->getHeight() + _target->getVy() <= this->getLimitY()) {
		if ((_target->getVy() * _dt) > _target->getY() - (this->getHeight() / 2)) { // may cause when target move too fast
			this->plusY(_target->getY() - (this->getHeight() / 2));
		}
		else {
			//this->plusY(_target->getVy() * _dt);
			this->setY(_target->getY() - (this->getHeight() / 2));
		}
	}
	else if (_target->getY() > this->getLimitY() - (this->getHeight() / 2)) {
		if (this->getY() + this->getHeight() < this->getLimitY()) {
			this->setY(this->getLimitY() - this->getHeight());
		}
	}
}

void Camera::load()
{
	// Read data from camera file
	string data = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->camera);
	vector<int> v = Tool::splitToVectorIntegerFrom(data, ',');

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);

	// Read data from map file
	data = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->map_info_man1);
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

void Camera::load(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setLimitX(v[0]);
	this->setLimitY(v[1]);
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
	FileManager::getInstance()->writeStringToTextFile(FilePath::getInstance()->camera, data);
}

