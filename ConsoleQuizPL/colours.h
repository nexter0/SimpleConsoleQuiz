// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#pragma once
#include <windows.h>
#include <string>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum Colour
{
	clGreen = 2, clDarkRed = 4, clPurple = 5, clDarkYellow = 6, clDefault = 7, clGrey = 8, clLime = 10, clCyan = 11, clRed = 12, clYellow = 14, clPink = 13, clWhite = 15
};

void __fastcall setColour(const Colour aColour);
void __fastcall resetColour();
void __fastcall printColoured(const Colour aColour, const std::string aText);

