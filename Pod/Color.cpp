#include "Color.h"

Color::Color(EnumColor _enumColor)
{
	this->value = _enumColor;
}

Color::~Color()
{
	delete& value;
}

EnumColor Color::getValue()
{
	return this->value;
}

void Color::setValue(EnumColor _enumColor)
{
	this->value = _enumColor;
}

D3DCOLOR Color::toD3DColor()
{
	switch (this->value)
	{
	case pinkFF00FF:
		return D3DCOLOR_XRGB(255, 0, 255);
	case black:
		return D3DCOLOR_XRGB(0, 0, 0);
	case blue9CFCF0:
		return D3DCOLOR_XRGB(156, 252, 240);
	default:
		return D3DCOLOR_XRGB(255, 255, 255);
		break;
	}
}
