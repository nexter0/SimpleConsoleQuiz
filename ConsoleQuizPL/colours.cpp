#include <windows.h>
// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#include <iostream>
#include "colours.h"

void __fastcall setColour(const Colour aColour)
{
	SetConsoleTextAttribute(hConsole, aColour);
}

void __fastcall resetColour()
{
	SetConsoleTextAttribute(hConsole, clDefault);
}

void __fastcall printColoured(const Colour aColour, const std::string aText)
{
	setColour(aColour);
	std::cout << aText;
	resetColour();
}
