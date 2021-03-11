#pragma once
#include "Rect.h"
#include "Color.h"
#include "Drawing.h"

class Component {
protected:
	Rect* bounds;
	Color* color;
public:
	Component(Rect* _bounds, Color* _color);
	~Component();

	// Getter
	Rect* getBounds();
	Color* getColor();

	// Setter
	void setBounds(Rect* _bounds);
	void setColor(Color* _color);

	virtual void update();
	virtual void draw();
};