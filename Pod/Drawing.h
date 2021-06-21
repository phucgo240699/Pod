#pragma once
#include "dxgraphics.h"
#include "ImagePath.h"

// Singleton
class Drawing {
private:
	Drawing()=default; // 1.Don't public constructor function
	static Drawing* instance; // 2. static private instance

	int cameraX, cameraY;

	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
	D3DXVECTOR2 scaleReverse = D3DXVECTOR2(-1, 1);
	D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0);

	LPDIRECT3DTEXTURE9 debugTexture = LoadTextureFromImage(ImagePath::getInstance()->debug_box, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 boardTexture = LoadTextureFromImage(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));
public:
	Drawing(const Drawing&) = delete; // 3. delete copy constructor
	static Drawing* getInstance();	  // 4. public function for client code usage

	int getCameraX();
	int getCameraY();

	void setCameraX(int _x);
	void setCameraY(int _y);

	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));

	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));

	void drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
};