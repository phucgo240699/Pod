#pragma once
#include "dxgraphics.h"
#include "Rect.h"

// Singleton
class Drawing {
private:
	Drawing()=default; // 1.Don't public constructor function
	static Drawing* instance; // 2. static private instance

	// Properties
	LPD3DXSPRITE spriteHandler;

public:
	Drawing(const Drawing&) = delete; // 3. delete copy constructor
	static Drawing* getInstance();	  // 4. public function for client code usage

	void draw(Size* _size, Rect* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, Color* _color);
	void draw(char* _fileName, Size* _size, Rect* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, Color* _color);
};