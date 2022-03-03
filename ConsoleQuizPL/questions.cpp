// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#include "questions.h"
#include "scores.h"
#include "colours.h"
#include <iostream>
#include <ctime>
#include <fstream>

QuestionType __fastcall QuestionsBase::getRandomCategory()
{
	int random;

	do {
		random = rand() % QuestionType::qtCount;
	} while (questions[random].empty()); // CHECK IF THE CATEGORY IS VALID

	return static_cast<QuestionType>(random);
}

bool __fastcall QuestionsBase::loadQuestions(const std::string aFileName)
{
	std::ifstream qFile;
	qFile.open(aFileName, std::ios::in);

	std::string category, inputQID, inputQText, inputAnsCorrect, inputQPoints, inputAnsArr[4];

	// ABORT IF FILE DOES NOT EXIST
	if (qFile.good() == false) return false; 

	while (qFile.good())
	{
		getline(qFile, category, TSV_SEPARATOR); // LOAD CATEGORY
		getline(qFile, inputQID, TSV_SEPARATOR); // LOAD ID (for debugging)
		getline(qFile, inputQText, TSV_SEPARATOR); // LOAD TEXT

		for (int i = 0; i < 4; i++)
		{
			getline(qFile, inputAnsArr[i], TSV_SEPARATOR); // LOAD ANSWERS
		}

		getline(qFile, inputAnsCorrect, TSV_SEPARATOR); // LOAD CORRECT ANSWER
		getline(qFile, inputQPoints, '\n');	// LOAD QUESTION VALUE

		// ADD QUESTION TO A CATEGORY
		questions[toQuestionType(category)].push_back({ stoi(inputQID), inputQText, {inputAnsArr[0], inputAnsArr[1], inputAnsArr[2], inputAnsArr[3]}, inputAnsCorrect[0], stoi(inputQPoints) });
	}

	qFile.close();

	return true;
}

void __fastcall QuestionsBase::removeQuestion(const QuestionType aCategory, const size_t aQuestionNumber)
{
	questions[aCategory].erase(questions[aCategory].begin() + aQuestionNumber);
}

int __fastcall QuestionsBase::questionsCount()
{
	int qCount = 0;

	for (auto category : questions)
	{
		qCount += category.size();
	}

	return qCount;
}

std::string __fastcall QuestionsBase::displayQuestion(const QuestionType aCategory, QuestionDetails* aDetails)
{
	std::string plAnswer;

	// SET QUESTION DETAILS
	aDetails->number = rand() % questions[aCategory].size();
	aDetails->correctAnswer = questions[aCategory][aDetails->number].ansCorrect;
	aDetails->value = questions[aCategory][aDetails->number].qPoints;
	aDetails->category = aCategory;

	printColoured(clDarkYellow, "Kategoria: ");
	std::cout << toPolish(aCategory) << "\n";
	printColoured(clDarkYellow, "To pytanie jest warte ");
	std::cout << questions[aCategory][aDetails->number].qPoints;
	setColour(clDarkYellow);
	std::cout << " " << checkPlural(questions[aCategory][aDetails->number].qPoints, "punkt", "punkty", "punktów") << ".\n\n";
	setColour(clYellow);
	std::cout << questions[aCategory][aDetails->number].qText << "\n";
	std::cout << " A) " << questions[aCategory][aDetails->number].ansArr[0] << "\n";
	std::cout << " B) " << questions[aCategory][aDetails->number].ansArr[1] << "\n";
	std::cout << " C) " << questions[aCategory][aDetails->number].ansArr[2] << "\n";
	std::cout << " D) " << questions[aCategory][aDetails->number].ansArr[3] << "\n";
	resetColour();
	std::cout << " > ";
	std::cin >> plAnswer;

	return plAnswer;
}

QuestionType __fastcall toQuestionType(const std::string aName)
{
	if (aName == "music")
	{
		return QuestionType::qtMusic;
	}
	if (aName == "history")
	{
		return QuestionType::qtHistory;
	}
	if (aName == "music")
	{
		return QuestionType::qtMusic;
	}
	if (aName == "science")
	{
		return QuestionType::qtScience;
	}
	if (aName == "entertainment")
	{
		return QuestionType::qtEntertainment;
	}
	if (aName == "geography")
	{
		return QuestionType::qtGeography;
	}

	return QuestionType::qtGeneral;
}

std::string __fastcall toPolish(const QuestionType aType)
{
	switch (aType)
	{
	case QuestionType::qtMusic: return "Muzyka";
	case QuestionType::qtHistory: return "Historia";
	case QuestionType::qtScience: return "Nauka";
	case QuestionType::qtEntertainment: return "Rozrywka";
	case QuestionType::qtGeography: return "Geografia";
	case QuestionType::qtGeneral: return "Wiedza ogólna";
	default: return "";
	}
}

std::string __fastcall checkPlural(const int aNumber, const std::string singularNominativ, const std::string pluralNominativ, const std::string pluralGenitive)
{
	if (aNumber == 1)
	{
		return singularNominativ;
	}
	else if (aNumber % 10 >= 2 && aNumber % 10 <= 4 && (aNumber % 100 < 10 || aNumber % 100 >= 20))
	{
		return pluralNominativ;
	}
	else
	{
		return pluralGenitive;
	}
}
