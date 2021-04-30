#pragma once
#include "dxgraphics.h"


// Singleton
class Drawing {
private:
	Drawing()=default; // 1.Don't public constructor function
	static Drawing* instance; // 2. static private instance

public:
	Drawing(const Drawing&) = delete; // 3. delete copy constructor
	static Drawing* getInstance();	  // 4. public function for client code usage

	void draw(LPDIRECT3DTEXTURE9 texture, RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	//void draw(LPDIRECT3DSURFACE9 surface, RECT* _srcRect, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
};