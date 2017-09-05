#pragma once

// keycodes http://nehe.gamedev.net/article/msdn_virtualkey_codes/15009/
class Input
{

public:
	static bool KeyPressed( char key );
	static bool KeyReleased( char key );
	static bool KeyHeldDown( char key );

	static bool keysPreviousFrame[ 256 ];
	static bool keys[ 256 ];
};
