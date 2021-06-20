#pragma once
#include "Component.h"

// Singleton
class Camera : public Component
{
private:
	static Camera* instance; // . static private instance

public:
	Camera(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	static Camera* getInstance();	  // . public function for client code usage

	void setPositionBy(Component* _target);
	void follow(Component* _target, float _dt);

	void load(string line, char seperator);
};

