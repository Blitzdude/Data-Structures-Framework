#include "Input.h"

bool Input::keysPreviousFrame[ 256 ] ={};
bool Input::keys[ 256 ] ={};

bool Input::KeyPressed( char key )
{
	if( !keysPreviousFrame[ key ] && keys[ key ] )
		return true;
	else
		return false;
}

bool Input::KeyReleased( char key )
{
	if( keysPreviousFrame[ key ] && !keys[ key ] )
		return true;
	else
		return false;
}

bool Input::KeyHeldDown( char key )
{
	if( keys[ key ] )
		return true;
	else
		return false;
}