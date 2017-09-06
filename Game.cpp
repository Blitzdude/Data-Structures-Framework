#include "Game.h"
#include <iostream>
#include "Input.h"
#include <Tchar.h> // _T 
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::cout;
using std::endl;

int seconds = 0;
void Game::Init(std::wstring *in_textToScreen)
{
	textToScreen = in_textToScreen;
	*textToScreen = _T( "Total Time : " );
	*textToScreen +=  std::to_wstring( seconds );
}

void Game::Update(double dt)
{
	totalTime += dt;

	if( totalTime > 1000 )
	{
		seconds++;
		*textToScreen = _T( "Total Time : " );
		*textToScreen +=  std::to_wstring( seconds );
		totalTime = 0;
	}

	if( Input::KeyPressed( VK_SPACE ) )
	{
		cout << "Space Key pressed" << endl;
	}
	else if (Input::KeyPressed( ( int )'W' ) )
	{
		cout << "W Key pressed" << endl;
	}
	else if (Input::KeyPressed( ( int )'A' ) )
	{
		cout << "A Key pressed" << endl;
	}
	else if (Input::KeyPressed( ( int )'S' ) )
	{
		cout << "S Key pressed" << endl;
	}
	else if (Input::KeyPressed( ( int )'D' ) )
	{
		cout << "D Key pressed" << endl;
	}

	if( Input::KeyHeldDown( VK_RETURN ) )
	{
		cout << "Enter button held down" << endl;
	}

	if( Input::KeyReleased( ( int )'Q' ) )
	{
		cout << "Q Key released" << endl;
	}
}

