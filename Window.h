#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Tchar.h> // _T 
#include <string>
#include "resource.h"
#include "Input.h"

std::wstring textToScreen = _T("not set");
LRESULT CALLBACK WindowProc( HWND	hwnd,
							 UINT	uMsg,
							 WPARAM	wParam,
							 LPARAM lParam )
{

	switch( uMsg )
	{
	case WM_CLOSE:
		MessageBox( hwnd, textToScreen.c_str(), _T( "Closing" ), MB_OK );
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
		PAINTSTRUCT ps;
		HDC hDC;
		char szBuffer[]="Hello, World!";
		hDC=BeginPaint( hwnd, &ps );

		TextOut( hDC, 10, 10, textToScreen.c_str(), textToScreen.length());
		EndPaint( hwnd, &ps );
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
	HINSTANCE hInstance		= GetModuleHandle( NULL );
	WNDCLASSEX windowClass	={};
	windowClass.cbSize		= sizeof( WNDCLASSEX );
	windowClass.style		= CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance	= hInstance;
	windowClass.lpszClassName = _T("VulkanWindowClass");
	
	windowClass.lpszMenuName = MAKEINTRESOURCE( IDR_MENU1 );
	RegisterClassEx( &windowClass );

	*outWindowHandle = CreateWindowEx
	(
		NULL,
		L"VulkanWindowClass",
		L"Hello Vulkan",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if( *outWindowHandle == NULL )
	{
		PostQuitMessage( 0 );
	}
}