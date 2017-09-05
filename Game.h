#pragma once
#include <string>
class Game
{
public:
	void Init(std::wstring *in_textToScreen);
	void Update(double dt);

private:
	double totalTime = 0;
	std::wstring *textToScreen;
};

