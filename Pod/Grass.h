#pragma once
#include "Component.h"
#include "Camera.h"

class Grass
{
private:
	Animation* animation;
	vector<RECT>* frames;
public:
	void loadAnimation(vector<string> data, char endSeperator, char seperator);
	void loadFrames(vector<string> data, char seperator);

	// Getter
	Animation* getAnimation();

	// Setter

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

