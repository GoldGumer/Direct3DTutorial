#include <Windows.h>
#include "Graphics.h"
#include <memory>

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(20);
		break;
	case WM_KEYDOWN:
		//WM_CHAR shows capitalization while WM_KEYDOWN just shows the character that was pressed
		if (wParam == 'A')
		{
			SetWindowText(hWnd, L"A pressed");
		}
		else if (wParam == 'W')
		{
			SetWindowText(hWnd, L"W pressed");
		}
		else if (wParam == 'D')
		{
			SetWindowText(hWnd, L"D pressed");
		}
		else if (wParam == 'S')
		{
			SetWindowText(hWnd, L"S pressed");
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE HPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	/*
	Window have 2 parts
		- Window part
			- Window is a class + instance
			- Class is anything in windows from buttons and dropdown menus to actual windows like in this case
			- Instance creates a class that can be put in different places
			- Not Direct3D
			- Used to draw Direct3D stuff into
		- Message part
			- Gets inputs for the window like exit, keycodes and cursor clicks
			- Is seperate from the window part
	*/

	//Name for the window
	const auto pClassName = L"Direct3D Window";
	//Setting parameters for the Window
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	//Registers Window
	RegisterClassEx(&wc);
	//Creates Window
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		L"D3D Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		200,
		200,
		640,
		480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	//Displays Window
	ShowWindow(hWnd, SW_SHOW);
	//Message Processing
	MSG msg;
	BOOL gResult;

	Graphics Gfx = Graphics(hWnd);

	//This is where the window is updated
	//Thus any graphics calls go in here which
	while (gResult = (GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//VVV Used for WM_CHAR VVV
		//TranslateMessage(&msg);
		//Drawing triangle
		Gfx.DrawTriangle();
		Gfx.EndFrame();
		DispatchMessage(&msg);
	}
	//Exit
	switch (gResult)
	{
	case -1:
		return -1;
		break;
	default:
		return msg.wParam;
		break;
	}
}