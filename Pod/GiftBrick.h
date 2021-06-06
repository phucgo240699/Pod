#pragma once
#include "Component.h"
#include "Camera.h"

class GiftBrick
{
private:
	Animation* animation;
	vector<RECT>* frames;
public:
	void loadAnimation(vector<string> data);
	void loadFrames(vector<string> data);

	// Getter
	Animation* getAnimation();

	// Setter
	
	

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

