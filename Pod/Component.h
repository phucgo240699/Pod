#pragma once
#include "Color.h"
#include "Drawing.h"

class Component {
protected:
	// General
	RECT* bounds;
	
	// Surface
	Color* color;
	D3DCOLOR d3dColor;
	LPDIRECT3DSURFACE9 surface;

	// Texture
	Color* transparentColor;
	D3DCOLOR d3dTransparentColor;
	LPDIRECT3DTEXTURE9 texture;
public:
	// Init
	Component(RECT* _bounds, Color* _color);
	Component(int x, int y, int width, int height, Color* _color);
	Component(int x, int y, LPCWSTR imagePath, Color* _transparentColor);


	// De Init
	~Component();

	// Getter
	RECT* getBounds();
	Color* getColor();

	// Setter
	void setBounds(RECT* _bounds);
	void setColor(Color* _color);

	virtual void Update();
	virtual void Draw();

	void jumpTo(int x, int y);
};