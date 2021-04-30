#pragma once
#include "FileManager.h"
#include "Drawing.h"

using namespace std;

class Animation
{
private:
	int id, indexFrame, animDelay, animCount;
	vector<RECT*>* frames;

public:
	// Init
	Animation(int _id, int _indexFrame, int _animDelay);
	Animation(int _id, int _indexFrame, int _animDelay, vector<RECT*>* _frames);
	Animation(int _id, int _indexFrame, int _animDelay, string filePath);

	// De Init
	~Animation();

	// Getter
	int getId();
	int getIndexFrame();
	int getAnimDelay();
	int getAnimCount();
	RECT* getCurrentFrame();
	int getTotalFrames();
	float getCurrentFrameWidth();
	float getCurrentFrameHeight();


	// Setter
	void setIndexFrame(int _indexFrame);
	void setAnimCount(int _animCount);


	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3* _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
};

