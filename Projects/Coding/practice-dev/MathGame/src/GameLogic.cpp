#include "GameStruct.h"
#include <iostream>

using namespace std;

int RandomNumber(int From, int To)
{
	int randNum = 0;

	randNum = rand() % (To - From + 1) + From;

	return (randNum);
}

void	ResetScreen()
{
	cout << "\033[33m";
	cout << "\033[0m";
}

short	ReadNumberOfQuestions()
{
	short NumberOfQuestions = 0;

	do
	{
		cout << "Please Enter Number Of Question, From 1 To 10 ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return (NumberOfQuestions);
}

enQuestionLevel	ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType	ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "\nEnter Operation Type [1]:Add, [2]:Sub, [3]:Mult, [4]:Div, [5]:MixOp ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
		case Add:
			return (Number1 + Number2);
		case Sub:
			return (Number1 - Number2);
		case Mult:
			return (Number1 * Number2);
		case Div:
			return (Number1 / Number2);
		default:
			return (Number1 + Number2);
	}
}

stQuestion	GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
			QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

	if (OperationType == enOperationType::MixOp)
			OperationType = (enOperationType)RandomNumber(1, 4);

	Question.QuestionLevel = QuestionLevel;
	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
		case Easy:
			Question.Number1 = RandomNumber(1, 10);
			Question.Number2 = RandomNumber(1, 10);
			break;

		case Med:
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);
			break;

		case Hard:
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);
			break;

		default:
			break;
	}

	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OperationType);

	return (Question);
}

void	GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

string	 GetOperationTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
		case Add:
			return "+";
		case Sub:
			return "-";
		case Mult:
			return "x";
		case Div:
			return "/";
		default:
			return "Mix";
	}
}

void	PrintQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << "\n";
	cout << "    " << GetOperationTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << "\n";
	cout << Quizz.QuestionList[QuestionNumber].Number2 << "\n";
	cout << "_______________\n";
}

int ReadPlayerAnswer()
{
	int Answer = 0;

	cout << " = ";
	cin >> Answer;

	return (Answer);
}

void	CorrecTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].ResultAnswer = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "\nWrong Answer :-(\n";
		cout << "The Right Answer = ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].ResultAnswer = true;
		Quizz.NumberOfRightAnswers++;

		cout << "\nRight Answer :-)\n";
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

void	AskAndCorrectQuestionAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrecTheQuestionAnswer(Quizz, QuestionNumber);
	}
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = {"Easy", "Med", "Hard", "Mixed"};
	return (arrQuestionLevelText[QuestionLevel - 1]);
}

string GetOperationTypeText(enOperationType OperationType)
{
	string arrOperationTypeText[5] = {"Add", "Sub", "Mult", "Div", "MixOp"};
	return (arrOperationTypeText[OperationType - 1]);
}

void PrintMathGameFinalResults(stQuizz Quizz)
{
	cout << "\n_________________________________________\n\n";
	cout << "          Final Result = " << GetFinalResultText(Quizz.isPass);
	cout << "\n_________________________________________\n";
	cout << "_________________________________________\n\n";
	cout << "Number Of Questions      : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level           : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;//hmtwuqlinC
	cout << "Operation Type           : " << GetOperationTypeText(Quizz.OperationType) << endl;//HMTWUOTINc
	cout << "Number Of Correct Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers  : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "_________________________________________\n";
}

void	PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadNumberOfQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionAnswers(Quizz);
	PrintMathGameFinalResults(Quizz);
}



void	StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\nDo You Want To Play Again Y/N ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

