#pragma once
#include "Component.h"

class Mario;

// Singleton
class Camera : public Component
{
private:
	static Camera* instance; // . static private instance

public:
	Camera(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	static Camera* getInstance();	  // . public function for client code usage

	// Getter
	RECT getFrame();

	void setX(float _x);
	void setY(float _y);
	void plusX(float _x);
	void plusY(float _y);
	void setPositionBy(Component* _target);
	void follow(Mario* _target, float _dt);

	void load(string line, char seperator);
};