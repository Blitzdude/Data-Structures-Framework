#include <iostream>
#include "Window.h"
#include "Game.h"
#include "Timer.h"
using std::cout;
using std::endl;

HANDLE consoleHandle;
HWND windowHandle;

Timer deltaTimer; // In-game Timer object
Game game; //

int main()
{
	InitConsole( &consoleHandle ); // Initialize console
	InitWindow( 640, 640, &windowHandle ); // Initialize Windows 

	Timer totalTime;
	totalTime.Start();
	deltaTimer.Start();

	game.Init(GetScreenText());

	MSG msg;
	while( true )
	{
		memcpy( Input::keysPreviousFrame, Input::keys, 256 );
		
		PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE );

		if( msg.message == WM_QUIT )
		{
			break;
		}

		TranslateMessage( &msg );
		DispatchMessage( &msg );

		double dt = deltaTimer.GetDuration();
		game.Update(dt);
		deltaTimer.Start();

		RedrawWindow( windowHandle, NULL, NULL, RDW_INVALIDATE );
	}

	printf( "program duration %.3f\n", totalTime.GetDuration() / 1000);
	return 0;
}