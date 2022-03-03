// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#pragma once
#include <string>
#include <vector>

struct Question
{
	int qID;
	std::string qText;
	std::string ansArr[4];
	char ansCorrect;
	int qPoints;
};

enum QuestionType
{
	qtMusic = 0, qtHistory, qtScience, qtEntertainment, qtGeography, qtGeneral,
	qtCount
};

struct QuestionDetails
{
	int number, value;
	char correctAnswer;
	QuestionType category;

	QuestionDetails() : number(0), value(0), correctAnswer(0), category(qtGeneral){}
};

QuestionType __fastcall toQuestionType(const std::string aName);
std::string __fastcall toPolish(const QuestionType aType);
std::string __fastcall checkPlural(const int aNumber, const std::string singularNominativ, const std::string pluralNominativ, const std::string pluralGenitive);

typedef std::vector<Question> QuestionCategories[QuestionType::qtCount];

class QuestionsBase
{
private:
	QuestionCategories questions; // std::vector<Question> questions[QuestionType::qtCount];

public:
	QuestionType __fastcall getRandomCategory();
	bool __fastcall loadQuestions(const std::string aFileName);
	void __fastcall removeQuestion(const QuestionType aCategory, const size_t aQuestionNumber);
	int __fastcall questionsCount();
	std::string __fastcall displayQuestion(const QuestionType aCategory, QuestionDetails* aDetails);
};