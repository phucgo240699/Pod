#pragma once
#include "Component.h"
#include "FileManager.h"

// Singleton
class Camera : public Component
{
private:
	static Camera* instance; // . static private instance

	float width, height;
	bool onTopSafeArea, onBottomSafeArea, onLeftSafeArea, onRightSafeArea = false;
public:
	Camera(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	static Camera* getInstance();	  // . public function for client code usage

	// Getter
	float getWidth();
	float getHeight();
	bool getOnTopSafeArea();
	bool getOnBottomSafeArea();
	bool getOnLeftSafeArea();
	bool getOnRightSafeArea();

	// Setter
	void setWidth(float _width);
	void setHeight(float _height);

	void setPositionBy(Component* _target);
	void follow(Component* _target, float _dt);

	void load();
	void save();
};

