#pragma once
#include "Color.h"
#include "Drawing.h"

class Component {
protected:
	RECT* bounds;
	Color* color;
	LPDIRECT3DSURFACE9 surface;
public:
	// Init
	Component(RECT* _bounds, Color* _color);
	Component(int x, int y, int width, int height, Color* _color);

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