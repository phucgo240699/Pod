#pragma once
#include "Drawing.h"

using namespace std;

class Animation
{
private:
	int id, currentIndexFrame, animDelay, animCount;
	vector<pair<RECT, RECT>>* frames; // First element in pair is bounds. Second element in pair is frame

public:
	// Init
	Animation(int _id, int _indexFrame, int _animDelay);
	Animation(int _id, int _indexFrame, int _animDelay, vector<pair<RECT, RECT>>* _frames);

	// Getter
	int getId();
	int getCurrentIndexFrame();
	int getTotalFrames();

	int getAnimDelay();
	int getAnimCount();

	RECT getCurrentBounds();
	RECT getCurrentFrame();

	int getCurrentBoundsWidth();
	int getCurrentBoundsHeight();
	int getCurrentFrameWidth();
	int getCurrentFrameHeight();


	// Setter
	void setCurrentIndexFrame(int _indexFrame);
	void setAnimCount(int _animCount);


	void Update(float _dt);
	//void Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(LPDIRECT3DTEXTURE9 _texture, RECT _srcRect, D3DXVECTOR3 _position);
	void DrawWithoutCamera(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void DrawMarioWithoutCamera(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, int _leftSpace, int _topSpace, int _rightSpace, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void DrawWithoutCamera(LPDIRECT3DTEXTURE9 _texture, RECT _srcRect, D3DXVECTOR3 _position);
};