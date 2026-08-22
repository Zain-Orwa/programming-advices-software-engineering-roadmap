#include "GameEnums.h"

struct	stQuestion
{
		int Number1 = 0;
		int Number2 = 0;
		enQuestionLevel QuestionLevel;
		enOperationType OperationType;
		int CorrectAnswer = 0;
		int PlayerAnswer = 0;
		bool ResultAnswer = false;
								
};

struct	stQuizz
{
		stQuestion QuestionList[100];
		short	NumberOfQuestions = 0;
		enQuestionLevel QuestionLevel;
		enOperationType OperationType;
		short NumberOfRightAnswers = 0;
		short NumberOfWrongAnswers = 0;
		bool isPass = false;
								
};


