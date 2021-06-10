#pragma once
#include "Component.h"
#include "Camera.h"

class StaticAnim
{
protected:
	Animation* animation;
	vector<RECT>* frames;
public:
	void loadAnimation(vector<string> data, char endSeperator, char seperator);
	void loadFrames(vector<string> data, char seperator);

	// Getter
	Animation* getAnimation();

	// Setter

	virtual void Update(float _dt);
	virtual void Draw(LPDIRECT3DTEXTURE9 _texture);
};

