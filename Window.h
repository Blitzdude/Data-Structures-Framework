#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Tchar.h> // _T 
#include <string>
#include "resource.h"
#include "Input.h"

std::wstring textToScreen = _T("not set");
HBITMAP g_bmp;


// This is the main message handler for the program
LRESULT CALLBACK WindowProc( HWND	hwnd,
							 UINT	uMsg,
							 WPARAM	wParam,
							 LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hDC;
		

	// sort through the messages
	switch( uMsg )
	{
	
	case WM_CLOSE:
		MessageBox( hwnd, textToScreen.c_str(), _T( "Closing - Goodbye cruel world" ), MB_OK );
		PostQuitMessage( 0 );
		break;
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case ID_FILE_EXIT:
			PostMessage( hwnd, WM_CLOSE, 0, 0 );
			break;
		}
		break;
	case WM_PAINT:
	{

		char szBuffer[]="Hello, World!";
		hDC=BeginPaint( hwnd, &ps );

		BITMAP bm;
		HDC memhDC = CreateCompatibleDC(hDC);
		HBITMAP hbmld = (HBITMAP)SelectObject(memhDC, g_bmp);
			
		GetObject(g_bmp, sizeof(bm), &bm);
		BitBlt(hDC, 100, 100, bm.bmWidth, bm.bmHeight, memhDC, 0, 0, SRCCOPY);
		TextOut(hDC, 40, 10, textToScreen.c_str(), textToScreen.length());
		SelectObject(memhDC, hbmld);
		DeleteDC(memhDC);


	}
		break;
	case WM_KEYDOWN:
		Input::keys[ wParam ] = true;
		switch( wParam )
		{
		case VK_ESCAPE:
			PostQuitMessage( 0 );
		}
		break;
	case WM_KEYUP:
		Input::keys[ wParam ] = false;	
		break;
	default:
	break;
	}
	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}

void InitConsole( HANDLE *outHandle )
{
	AllocConsole();
	AttachConsole( GetCurrentProcessId() );
	freopen( "CON", "w", stdout );
	freopen( "CON", "r", stdin );
	*outHandle = GetStdHandle( STD_INPUT_HANDLE );
	if( *outHandle == NULL )
	{
		PostQuitMessage( 0 );
	}
}

std::wstring *GetScreenText()
{
	return &textToScreen;
}

void InitWindow( int width, int height, HWND *outWindowHandle )
{
	// fill in the struct with the needed information
	HINSTANCE hInstance		= GetModuleHandle( NULL );
	WNDCLASSEX windowClass	={};
	

	windowClass.cbSize		= sizeof( WNDCLASSEX );
	windowClass.style		= CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance	= hInstance;
	windowClass.lpszClassName = _T("VulkanWindowClass");
	
	windowClass.lpszMenuName = MAKEINTRESOURCE( IDR_MENU1 );

	// Register the window class
	if (!RegisterClassEx(&windowClass)) 
	{
		MessageBox(NULL, _T("Window registeration failed"), _T("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
	}

	// Create the window and use the result as the handle
	*outWindowHandle = CreateWindowEx
	(
		NULL,
		L"VulkanWindowClass",	// name of the window class
		L"Hello Vulkan",		// Title of the windows
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, // windowstyle and visible
		100, 100,				// x and y-positions of the window
		width, height,			// width and height of the window
		NULL,					// No Parent window
		NULL,					// We are not using menues
		hInstance,				// application handle
		NULL					// used with multiple windows, NULL
	);

	g_bmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	if (g_bmp == NULL)
	{
		MessageBox(*outWindowHandle, _T("Could not load IDB_BITMAP2"), _T("Error"),
			MB_OK | MB_ICONEXCLAMATION);

	}

	if( *outWindowHandle == NULL )
	{
		PostQuitMessage( 0 );
	}
}