#pragma once
#include "Component.h"

class View : public Component
{
private:
	// Properties
	RECT* bounds;
	D3DCOLOR color;

	LPDIRECT3DSURFACE9 surface;
public:
	// Init
	View(RECT* rect, D3DCOLOR _color);
	View(int x, int y, int width, int height, D3DCOLOR _color);

	// De Init
	~View();

	// Inherit
	void Update();
	void Draw();
	void setColor(D3DCOLOR _color);
};

