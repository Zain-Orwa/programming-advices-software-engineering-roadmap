#include "GameStruct.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int RandomNumber(int From, int To);
void	ResetScreen();
short	ReadNumberOfQuestions();
enQuestionLevel	ReadQuestionLevel();
enOperationType	ReadOperationType();
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType);
stQuestion	GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType);
void	GenerateQuizzQuestion(stQuizz& Quizz);
string	 GetOperationTypeSymbol(enOperationType OperationType);
void	PrintQuestion(stQuizz& Quizz, short QuestionNumber);
int ReadPlayerAnswer();
void	CorrecTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber);
void	AskAndCorrectQuestionAnswers(stQuizz& Quizz);
string GetFinalResultText(bool Pass);
string GetQuestionLevelText(enQuestionLevel QuestionLevel);
string GetOperationTypeText(enOperationType OperationType);
void PrintMathGameFinalResults(stQuizz Quizz);
void	PlayMathGame();
void	StartGame();
