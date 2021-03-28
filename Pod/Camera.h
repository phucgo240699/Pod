#pragma once
#include "Component.h"
#include "FileManager.h"

// Singleton
class Camera : public Component
{
private:
	static Camera* instance; // . static private instance

	float width, height;

public:
	Camera(float _x, float _y);
	static Camera* getInstance();	  // . public function for client code usage

	// Getter
	float getWidth();
	float getHeight();

	// Setter
	void setWidth(float _width);
	void setHeight(float _height);

	void load();
	void save();
};

