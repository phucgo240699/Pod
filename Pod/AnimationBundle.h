#pragma once
#include <unordered_map>
#include "Animation.h"
#include "Drawing.h"

using namespace std;

class AnimationBundle
{
private:
	LPDIRECT3DTEXTURE9 texture;
	unordered_map<int, Animation>* animations;

public:
	// Init
	AnimationBundle(LPCWSTR _imagePath, string _animationsPath, D3DCOLOR _transcolor);
	AnimationBundle(LPDIRECT3DTEXTURE9 _texture, string _animationsPath);

	// De-Init
	~AnimationBundle();
	
	void Update();
	void Draw();
};
