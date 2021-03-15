#pragma once
#include "Color.h"
#include "Drawing.h"

class Component {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void setColor(D3DCOLOR _color) = 0;
};