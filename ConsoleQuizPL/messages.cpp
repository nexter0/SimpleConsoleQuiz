// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#include <string>
#include "messages.h"
#include "questions.h"
#include "colours.h";
#include <limits>
#include <cstddef>
#define NOMINMAX

void __fastcall displayWelcome()
{
	printColoured(clDarkYellow, "Witaj w Console Quiz!\n");
	printColoured(clYellow, "Prosta konsolowa minigra napisana w C++, w której sprawdzisz swoją wiedzę!\n");
	printColoured(clDarkYellow, "=====================================================\n");
	setColour(clYellow);
	std::cout << "Ładowanie pytań...\n" << ".\n" << ".\n" << ".\n";
	resetColour();
}

void __fastcall displayNoFile()
{
	setColour(clRed);
	std::cout << "Ups! Mamy problem!\n\n";
	std::cout << "Upewnij się, że w folderze z programem znajduje się plik questions.tsv i uruchom program ponownie.\n";
	resetColour();
}


void __fastcall displayStats(QuestionsBase aQuestions, const int aLives, const int aScore, const int aStreak)
{
	printColoured(clDarkYellow, "=======================================\n");
	std::cout << "  Szanse: ";
	switch(aLives)
	{
	case 3: { setColour(clGreen); break; }
	case 2: { setColour(clDarkYellow); break; }
	case 1: { setColour(clRed); break; }
	default: { setColour(clCyan); break; }
	}
	for (int i = 0; i < aLives; i++) { std::cout << 'X'; }
	resetColour();
	std::cout << "\n  Wynik: ";
	printColoured(clYellow, std::to_string(aScore));
	std::cout << "\n  Seria: ";
	printColoured(clYellow, std::to_string(aStreak));
	std::cout << "\n  Pozostałe pytania: ";
	printColoured(clYellow, std::to_string(aQuestions.questionsCount()));
	printColoured(clDarkYellow, "\n=======================================\n\n");
}

void __fastcall wait()
{
	using namespace std;

	printColoured(clYellow, "Naciśnij dowolny klawisz, aby kontynuować...");
	//system("pause>0");
#undef max
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}
