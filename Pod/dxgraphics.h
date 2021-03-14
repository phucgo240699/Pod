#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Setting.h"


#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H

// function prototypes
int Init_Direct3D(HWND hwnd, int width, int height, bool isFullScreen);
LPDIRECT3DSURFACE9 LoadBlankSurface(Size* size);
LPDIRECT3DSURFACE9 LoadSurfaceFromFile(char* fileName, D3DCOLOR transcolor);
LPDIRECT3DTEXTURE9 LoadBlankTexture(Size* size);
LPDIRECT3DTEXTURE9 LoadTextureFromFile(char* fileName, D3DCOLOR transcolor);

// variable declarations
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern D3DPRESENT_PARAMETERS d3dpp;
extern LPDIRECT3DSURFACE9 backbuffer;
#endif