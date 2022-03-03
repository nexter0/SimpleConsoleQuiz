// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#include "scores.h"
#include "colours.h"
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

TotalScore* TotalScore::empty = new TotalScore(0, 0, 0, 0, "");

TotalScore::TotalScore(int aScore, int aStreak, int aAnsweredQuestions, int aHighestStreak, std::string aDateTime)
{
	this->score = aScore;
	this->streak = aStreak;
	this->answeredQuestions = aAnsweredQuestions;
	this->highestStreak = aHighestStreak;

	if (aDateTime == "")
	{
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		const char* months[12] = { "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "PaŸ", "Lis", "Gru" };

		this->datetime += std::to_string(newtime.tm_mday);

		this->datetime += " ";
		this->datetime += months[newtime.tm_mon];
		this->datetime += " ";

		this->datetime += std::to_string(1900 + newtime.tm_year);

		this->datetime += " " + ((newtime.tm_hour > 10) ? std::to_string(newtime.tm_hour) : "0" + std::to_string(newtime.tm_hour)) + ":";
		this->datetime += ((newtime.tm_min > 10) ? std::to_string(newtime.tm_min) : "0" + std::to_string(newtime.tm_min)) + ":";
		this->datetime += ((newtime.tm_sec > 10) ? std::to_string(newtime.tm_sec) : "0" + std::to_string(newtime.tm_sec));
	}
	else
	{
		this->datetime = aDateTime;
	}
}

void __fastcall TotalScore::saveScore()
{
	std::ofstream sFile;
	sFile.open("scores.tsv", std::ios::app);

	sFile << this->datetime << TSV_SEPARATOR;
	sFile << this->score << TSV_SEPARATOR;
	sFile << this->streak << TSV_SEPARATOR;
	sFile << this->highestStreak << TSV_SEPARATOR;
	sFile << this->answeredQuestions << "\n";

	sFile.close();

	printColoured(clLime, "\nWynik zapisany.\n");
}

void __fastcall TotalScore::printScore(bool isFirstLine)
{
	if (isFirstLine)
	{
		std::cout << "\n DATE & TIME            SCORE   STREAK   HI-STREAK   QUESTIONS\n ";
	}
	if (!isFirstLine) std::cout << " ";
	std::cout << this->datetime << "       ";
	std::cout << this->score << "        ";
	std::cout << this->streak << "           ";
	std::cout << this->highestStreak << "           ";
	std::cout << this->answeredQuestions << "\n";
	if (isFirstLine)
	{
		std::cout << "\n";
	}
}

bool __fastcall TotalScore::saveQuery()
{
	std::string plAnswer;

	while (true)
	{
		printColoured(clYellow, "\nCzy chcesz zapisaæ wynik? (T/N)\n");
		std::cin >> plAnswer;

		if (plAnswer.length() != 1)
		{
			printColoured(clPurple, "Niepoprawny wybór.\n");
			continue;
		}
		else if (toupper(plAnswer.at(0)) == 'T')
		{
			return true;
		}
		else if (toupper(plAnswer.at(0)) == 'N')
		{
			return false;
		}
		printColoured(clPurple, "Niepoprawny wybór.\n");

	}
}

bool TotalScore::scoresFileExist()
{
	bool result;
	std::fstream sFile;

	sFile.open("scores.tsv", std::ios::in);
	result = (sFile.good());
	sFile.close();

	return result;
}

TotalScore* TotalScore::clone()
{
	return new TotalScore(this->score, this->streak, this->answeredQuestions, this->highestStreak, this->datetime);
}

int TotalScore::getScore()
{
	return score;
}

std::string TotalScore::getDateTime()
{
	return datetime;
}

