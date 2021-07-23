#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include "dxgraphics.h"
#include "ImagePath.h"

class Camera;

// Singleton
class Drawing {
private:
	Drawing()=default; // 1.Don't public constructor function
	static Drawing* instance; // 2. static private instance

	//int cameraX, cameraY;

	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
	D3DXVECTOR2 scaleReverse = D3DXVECTOR2(-1, 1);
	D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0);


	LPDIRECT3DTEXTURE9 debugTexture = LoadTextureFromImage(ImagePath::getInstance()->debug_box, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 boardTexture = LoadTextureFromImage(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 worldMapTexture = LoadTextureFromImage(ImagePath::getInstance()->world_map, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 sunnyMapTexture;
	LPDIRECT3DTEXTURE9 undergroundMapTexture;
	LPDIRECT3DTEXTURE9 thirdMapTexture;
	LPDIRECT3DTEXTURE9 cloudyMapTexture;


public:
	Drawing(const Drawing&) = delete; // 3. delete copy constructor
	static Drawing* getInstance();	  // 4. public function for client code usage

	// Getter
	LPDIRECT3DTEXTURE9 getWorldMapTexture();
	LPDIRECT3DTEXTURE9 getSunnyMapTexture();
	LPDIRECT3DTEXTURE9 getUndergroundMapTexture();
	LPDIRECT3DTEXTURE9 getThirdMapTexture();
	LPDIRECT3DTEXTURE9 getCloudyMapTexture();

	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void draw(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));

	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawMarioWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, int _leftSpace, int _topSpace, int _rightSpace, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));

	void drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
	void drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color = D3DCOLOR_XRGB(255, 255, 255));
};
#endif // !DRAWING_H