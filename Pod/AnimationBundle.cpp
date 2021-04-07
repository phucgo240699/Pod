#include "AnimationBundle.h"

AnimationBundle::AnimationBundle(LPCWSTR _imagePath, string _animationsPath, D3DCOLOR _transcolor)
{
	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	// read animations from text file
}

AnimationBundle::AnimationBundle(LPDIRECT3DTEXTURE9 _texture, string _animationsPath)
{
	this->texture = _texture;
	// read animations from text file
}

AnimationBundle::~AnimationBundle()
{
	delete& texture;
	delete animations;
}
