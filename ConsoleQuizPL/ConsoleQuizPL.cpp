// SIMPLE CONSOLE QUIZ (PL)
// Nikodem Przybyszewski 2021

#include <iostream>
#include <locale.h>
// HEARDER FILES
#include "scores.h"
#include "questions.h"
#include "messages.h"
#include "colours.h"

int run()
{
	std::string plAnswer;
	QuestionsBase* questions = new QuestionsBase();
	QuestionDetails* details = new QuestionDetails();
	Stats* stats = new Stats();

	setlocale(LC_ALL, "Polish");
	srand(time(NULL));

	displayWelcome();

	if (questions->loadQuestions("questions.tsv"))
	{
		setColour(clLime);
		std::cout << "Gotowe!\n\n";
		std::cout << "Za³adowano " << questions->questionsCount() << " " << checkPlural(questions->questionsCount(), "pytanie", "pytania", "pytañ") << "\n\n";
		setColour(clYellow);
		printColoured(clDarkYellow, "Zasady s¹ proste.\n ");
		std::cout << "> Masz 3 szanse i twoim celem jest zdobycie jak najwiêkszej liczby punktów.\n > Za pytania mo¿esz otrzymaæ 1, 2 lub 3 punkty. Odpowiadaj¹c poprawnie, zdobywasz seriê.\n > 5 poprawnych odpowiedzi daje Ci dodatkow¹ szansê.\n\n";
		resetColour();
		wait();
		system("cls");

		while (stats->lives > 0 && questions->questionsCount() > 0)
		{
			displayStats(*questions, stats->lives, stats->score, stats->streak);

			// DISPLAY QUESITON & GET ANSWER
			plAnswer = questions->displayQuestion(questions->getRandomCategory(), details); 

			// CHECKING ANSWER
			while (true) 
			{
				if (toupper(plAnswer.at(0)) != 'A' && toupper(plAnswer.at(0)) != 'B' && toupper(plAnswer.at(0)) != 'C' && toupper(plAnswer.at(0)) != 'D' || plAnswer.length() != 1)
				{
					// INVALID ANSWER
					printColoured(clPink, "Niepoprawny wybór. Spróbuj ponownie.\n");
					std::cout << " > ";
					std::cin >> plAnswer;
				}
				else if (toupper(plAnswer.at(0)) == details->correctAnswer)
				{
					// CORRECT ANSWER
					int newPoints = details->value + details->value * stats->streak;

					printColoured(clLime, "Poprawna odpowiedŸ!\n");
					setColour(clGreen);
					std::cout << "Otrzymujesz " << newPoints << " " << checkPlural(newPoints, "punkt", "punkty", "punktów") << ".\n";
					resetColour();
					stats->score += newPoints;
					stats->streak++;

					if (stats->streak > stats->highestStreak) stats->highestStreak = stats->streak;
					if (stats->streak % 5 == 0 && stats->streak != 0)
					{
						if (stats->lives < 5)
						{
							printColoured(clCyan, "\nŒwietnie! Zdobywasz dodatkow¹ szansê!\n");
							stats->lives++;
						}
						else
						{
							int newPoints = 3 * stats->streak;

							setColour(clCyan);
							std::cout << "\nMasz ju¿ maksymaln¹ iloœæ szans, wiêc otrzymujesz dodatkowo " << newPoints << " " << checkPlural(newPoints, "punkt", "punkty", "punktów") << "\n";
							resetColour();
							stats->score += newPoints;
						}
					}
					stats->answeredQuestions++;
					questions->removeQuestion(details->category, details->number);
					wait();
					break;
				}
				else
				{
					// WRONG ANSWER
					printColoured(clRed, "Z³a odpowiedŸ...\n");
					printColoured(clYellow, "Poprawn¹ odpowiedzi¹ by³o ");
					printColoured(clGreen, std::string(1, details->correctAnswer));
					std::cout << "\n";

					stats->streak = 0;
					stats->lives--;
					stats->answeredQuestions++;
					questions->removeQuestion(details->category, details->number);
					wait();
					break;
				}
			}
			//wait();
			system("cls");
		}
	}
	else 
	{
		// NO QUESTIONS FILE FOUND
		displayNoFile();
		wait();
		return 0;
	}

	TotalScore* currentScore = new TotalScore(stats->score, stats->streak, stats->answeredQuestions, stats->highestStreak);

	system("cls");
	displayStats(*questions, stats->lives, stats->score, stats->streak);

	if (stats->lives == 0) printColoured(clPurple, "Koniec szans. Tak czy siak, dobra robota!\n");
	else printColoured(clPink, "Skoñczy³y siê pytania. Dobra robota!\n");

	if (TotalScore::saveQuery()) currentScore->saveScore();
	else goto DELETE_SECTION;

	if (TotalScore::scoresFileExist())
	{
		// PRINT SCOREBOARD
		std::string tempDateTime, tempScore, tempStreak, tempHStreak, tempAnsQuestions;
		TotalScore* highScore = TotalScore::empty;

		std::ifstream sFile;
		sFile.open("scores.tsv", std::ios::in);

		std::cout << "Poprzednie wyniki:\n";

		while (sFile.good())
		{
			//cin.ignore();
			getline(sFile, tempDateTime, TSV_SEPARATOR);
			getline(sFile, tempScore, TSV_SEPARATOR);
			getline(sFile, tempStreak, TSV_SEPARATOR);
			getline(sFile, tempHStreak, TSV_SEPARATOR);
			getline(sFile, tempAnsQuestions, '\n');

			TotalScore loadedScore(stoi(tempScore), stoi(tempStreak), stoi(tempAnsQuestions), stoi(tempHStreak), tempDateTime);

			// AVOID DISPLAYING CURRENT SCORE IN PREVIOUS SCORES
			if (loadedScore.getDateTime() == currentScore->getDateTime()) 
			{
				break;
			}

			loadedScore.printScore(false);

			if (loadedScore.getScore() >= highScore->getScore())
			{
				if (highScore != nullptr && highScore != TotalScore::empty)
				{
					delete highScore;
				}
				highScore = loadedScore.clone();
			}
		}

		std::cout << "\nNajlepszy wynik:\n";
		setColour(clPink);
		highScore->printScore(false);
		resetColour();
		wait();
	}

	// END OF THE PROGRAM
	DELETE_SECTION:
		delete currentScore;
		delete stats;
		delete details;
		delete questions;

	return 0;
}

int main()
{
	try
	{
		run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::ofstream f("error.log");
		f << e.what() << std::endl;
		f.close();
		return EXIT_FAILURE;
	}
}