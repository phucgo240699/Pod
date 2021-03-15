#pragma once
#include "Component.h"


class Rectangle : public Component
{
protected:
	// General
	int width, height;
	vector<D3DXVECTOR3*> positions;
	
	// Surface
	D3DCOLOR color;
	LPDIRECT3DSURFACE9 surface;

	// Texture
	D3DCOLOR transparentColor;
	LPDIRECT3DTEXTURE9 texture;
public:
	// Init


	// De Init
	~Component();

	virtual void Update();
	virtual void Draw();
};

