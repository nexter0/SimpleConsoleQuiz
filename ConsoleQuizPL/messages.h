// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#pragma once
#include <iostream>
#include "questions.h"

void __fastcall displayWelcome();
void __fastcall displayNoFile();
void __fastcall displayStats(QuestionsBase aQuestions, const int aLives, const int aScore, const int aStreak);
void __fastcall wait();
