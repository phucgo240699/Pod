#pragma once
#include "Color.h"
#include "Drawing.h"

class Component {
protected:
	RECT* bounds;
	Color* color;
	LPDIRECT3DSURFACE9 surface;
public:
	Component(RECT* _bounds, Color* _color);
	Component(int x, int y, int width, int height, Color* _color);
	~Component();

	// Getter
	RECT* getBounds();
	Color* getColor();

	// Setter
	void setBounds(RECT* _bounds);
	void setColor(Color* _color);

	virtual void update();
	virtual void draw();
};