#include "dxgraphics.h"


LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
D3DPRESENT_PARAMETERS d3dpp;
LPDIRECT3DSURFACE9 backbuffer = NULL;
LPD3DXSPRITE spriteHandler = NULL;


int Init_Direct3D(HWND hwnd, int width, int height, bool isFullScreen)
{
	// Init Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(hwnd, L"********Create Direct3D failed********", L"Error", MB_OK);
		return 0;
	}

	// Direct3D params
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = Setting::getInstance()->getScreenMode() == window ? TRUE : FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = Setting::getInstance()->getScreenWidth();
	d3dpp.BackBufferHeight = Setting::getInstance()->getScreenHeight();
	d3dpp.hDeviceWindow = hwnd;


	// Init Direc3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);
	if (d3ddev == NULL) {
		MessageBox(hwnd, L"********Create Direct3D device failed********", L"Error", MB_OK);
		return 0;
	}


	// Init sprite handler
	if (D3DXCreateSprite(d3ddev, &spriteHandler) != D3D_OK) {
		MessageBox(hwnd, L"********Create sprite handler failed********", L"Error", MB_OK);
		return 0;
	}

	// Clear backbuffer
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// Reference to backbuffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);


	return 1;
}

LPDIRECT3DSURFACE9 LoadBlankSurface(int width, int height)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	HRESULT result;

	// Create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		width,
		height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL
	);

	if (result != D3D_OK) {
		throw "Create surface failed";
		return NULL;
	}

	return surface;
}

//LPDIRECT3DSURFACE9 LoadSurfaceFromFile(char* fileName, D3DCOLOR transcolor)
//{
//	LPDIRECT3DSURFACE9 surface = NULL;
//	D3DXIMAGE_INFO info;
//	HRESULT result;
//
//	// get size of file
//	result = D3DXGetImageInfoFromFile(Tool::getLPCWSTRFromCharArray(fileName), &info);
//	if (result != D3D_OK) {
//		return NULL;
//	}
//
//
//	// Create surface
//	result = d3ddev->CreateOffscreenPlainSurface(
//		info.Width,
//		info.Height,
//		D3DFMT_X8R8G8B8,
//		D3DPOOL_DEFAULT,
//		&surface,
//		NULL
//	);
//
//	if (result != D3D_OK) {
//		return NULL;
//	}
//
//	// Load surface from file
//	result = D3DXLoadSurfaceFromFile(
//		surface,
//		NULL,
//		NULL,
//		Tool::getLPCWSTRFromCharArray(fileName),
//		NULL,
//		D3DX_DEFAULT,
//		transcolor,
//		NULL
//	);
//	if (result != D3D_OK) {
//		return NULL;
//	}
//
//
//	return surface;
//}

LPDIRECT3DTEXTURE9 LoadTextureFromImage(LPCWSTR imagePath, D3DCOLOR transcolor)
{
	// texture pointer
	LPDIRECT3DTEXTURE9 texture = NULL;

	// Structure for read information from bitmap file
	D3DXIMAGE_INFO info;

	// Return value
	HRESULT result;

	// Get info width & height from bitmap file
	result = D3DXGetImageInfoFromFile(imagePath, &info);

	// Check if get info failed
	if (result != D3D_OK) {
		throw "Get image info failed. Please check your path";
		return NULL;
	}

	// Create new texture from bitmap
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		imagePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transcolor,
		&info,
		NULL,
		&texture);


	// Make sure create texture successful
	if (result != D3D_OK) {
		throw "Create texture from file failed";
		return NULL;
	}

	return texture;
}
