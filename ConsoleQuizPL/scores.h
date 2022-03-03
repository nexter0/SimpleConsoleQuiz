// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#pragma once
#include <string>
#include <fstream>

const char TSV_SEPARATOR = (char)9;

struct Stats
{
public:
	int lives, score, streak, highestStreak, answeredQuestions;

	Stats() : lives(3), score(0), streak(0), highestStreak(0), answeredQuestions(0){}
};

class TotalScore
{
private:

	int score, streak, answeredQuestions, highestStreak;
	std::string datetime;

public:

	TotalScore(int aScore, int aStreak, int aAnsweredQuestions, int aHighestStreak, std::string aDateTime = "");

	void __fastcall saveScore();
	void __fastcall printScore(bool isFirstLine);

	static bool __fastcall saveQuery();
	static bool scoresFileExist();

	TotalScore* __fastcall clone();

	int __fastcall getScore();
	std::string __fastcall getDateTime();

	static TotalScore* empty;
};

