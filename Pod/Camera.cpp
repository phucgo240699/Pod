#include "Camera.h"
#include "Mario.h"

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


RECT Camera::getFrame()
{
	RECT r;
	r.top = this->getY();
	r.bottom = this->getY() + this->getHeight();
	r.left = this->getX();
	r.right = this->getX() + this->getWidth();
	return r;
}

void Camera::setX(float _x)
{
	Component::setX(_x);
}

void Camera::setY(float _y)
{
	Component::setY(_y);
}

void Camera::plusX(float _x)
{
	Component::plusX(_x);
}

void Camera::plusY(float _y)
{
	Component::plusY(_y);
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

void Camera::follow(Mario* _target, float _dt)
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

	if (_target->getIsFlyingUpMode() == false && this->getY() + this->getHeight() >= this->getLimitY()) {
		if (_target->getY() > this->getLimitY() - (this->getHeight() / 2)) {
			if (this->getY() + this->getHeight() < this->getLimitY()) {
				this->setY(this->getLimitY() - this->getHeight());
			}
		}
		return;
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

void Camera::load(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
	this->setWidth(v[4]);
	this->setHeight(v[5]);
	this->setLimitX(v[6]);
	this->setLimitY(v[7]);
}

void Camera::loadWorldMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->camer_world_map, ios::in);

	vector<string> v;
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty
		this->load(line, ',');
	}

	fs.close();
}

void Camera::loadSunnyMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->camera_sunny_map, ios::in);

	vector<string> v;
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty
		this->load(line, ',');
	}

	fs.close();
}

void Camera::loadUndergroundMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->camera_underground_map, ios::in);

	vector<string> v;
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty
		this->load(line, ',');
	}

	fs.close();
}
