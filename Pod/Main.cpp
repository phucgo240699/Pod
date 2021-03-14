// source code Windows

#include"AppConfig.h"
#include <iostream>

AppConfig* appConfig = new AppConfig();
AppController* appController = appConfig->appController;
Setting* setting = appConfig->setting;


// window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		// release the Direct3D device
		if (d3ddev != NULL)
			d3ddev->Release();

		// release the Direct3D object
		if (d3d != NULL)
			d3d->Release();

		// call the "front-end" shutdown function
		appController->Game_End(hWnd);

		// tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


// helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance) {
	// Create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	// fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = setting->getAppTitleAsLPCWSTR();
	wc.hIconSm = NULL;

	// set up the window with the class info
	return RegisterClassEx(&wc);
}



// entry pont for a Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	HWND hWnd;

	// register the class
	MyRegisterClass(hInstance);

	// set up the creen in windowed or fullscreen mode?
	DWORD style;
	if (setting->getScreenMode() == fullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else style = WS_OVERLAPPED;

	// create a new window
	hWnd = CreateWindow(
		setting->getAppTitleAsLPCWSTR(),
		setting->getAppTitleAsLPCWSTR(),
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		setting->getScreenSize()->getWidth(),
		setting->getScreenSize()->getHeight(),
		NULL,
		NULL,
		hInstance,
		NULL);

	// was there an error creating the window?
	if (!hWnd)
		return FALSE;

	// display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!Init_Direct3D(hWnd, setting->getScreenSize()->getWidth(), setting->getScreenSize()->getHeight(), setting->getScreenMode() == fullScreen))
		return 0;

	// initialize the game
	if (!appController->Game_Init(hWnd)) {
		MessageBox(hWnd, Tool::getLPCWSTRFromCharArray("Error initializing the game"), Tool::getLPCWSTRFromCharArray("Error"), MB_OK);
		return 0;
	}


	// main message loop
	int done = 0;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// look for quit messgae
			if (msg.message == WM_QUIT)
				done = 1;

			// decode and pass messages on to WindProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else appController->Game_Run(hWnd);
	}
	return msg.wParam;
}