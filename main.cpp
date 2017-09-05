#include <iostream>
#include <d3d9.h>
#include "Window.h"
#include "Game.h"
#include "Timer.h"
using std::cout;
using std::endl;

HANDLE consoleHandle;
HWND windowHandle;

Timer deltaTimer; // In-game Timer object
Game game; // game-manager object

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
		
		// Check to see if any messages are waiting in the queue
		PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE );

		// if next message is quit, exit while-loop
		if( msg.message == WM_QUIT )
		{
			break;
		}
		
		// Translate keystroke messages into the right format
		TranslateMessage( &msg );

		// Send the message to the WindowProc function
		DispatchMessage( &msg );

		// Run game code here
		double dt = deltaTimer.GetDuration();
		game.Update(dt);
		deltaTimer.Start();

		RedrawWindow( windowHandle, NULL, NULL, RDW_INVALIDATE );
	}

	printf( "program duration %.3f\n", totalTime.GetDuration() / 1000);
	return 0;
}