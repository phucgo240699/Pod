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
	case red:
		return D3DCOLOR_XRGB(255, 0, 0);
	case orange:
		return D3DCOLOR_XRGB(255, 165, 0);
	case yellow:
		return D3DCOLOR_XRGB(255, 255, 0);
	case green:
		return D3DCOLOR_XRGB(0, 255, 0);
	case blue:
		return D3DCOLOR_XRGB(0, 0, 255);
	case pinkFF00FF:
		return D3DCOLOR_XRGB(255, 0, 255);
	case purple:
		return D3DCOLOR_XRGB(128, 0, 128);
	case black:
		return D3DCOLOR_XRGB(0, 0, 0);
	case gray:
		return D3DCOLOR_XRGB(128, 128, 128);
	default:
		return D3DCOLOR_XRGB(255, 255, 255);
		break;
	}
}
