#include "GameStruct.h"
#include <iostream>

using namespace std;

int RandomNumber(int From, int To)
{
	int randNum = 0;

	randNum = rand() % (To - From + 1) + From;

	return (randNum);
}

short ReadHowManyRound()
{
	short RoundNumber = 0;

	do
	{
		cout << "How Many Round Would You Like To Play, From 1 To 10 ? ";
		cin >> RoundNumber;

	} while (RoundNumber < 1 || RoundNumber > 10);

	return (RoundNumber);
}

enGameChoice	ReadPlayer1Choice()
{
	short Choice = 0;

	do
	{
		cout << "Enter Your Choice [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return (enWinner::Draw);

	switch (RoundInfo.Player1Choice)
	{
		case Stone:
			if (RoundInfo.ComputerChoice == enGameChoice::Paper)
				return (enWinner::Computer);
			break;

		case Paper:
			if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
				return (enWinner::Computer);
			break;

		case Scissors:
			if (RoundInfo.ComputerChoice == enGameChoice::Stone)
				return (enWinner::Computer);
			break;
	}
	
	return (enWinner::Player1);
}

string	WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = {"Player1", "Computer", "No Winner"};

	return (arrWinnerName[Winner - 1]);
}

string ChoicName(enGameChoice Choice)
{
	string arrChoiceName[3] = {"Stone", "Paper", "Scissors"};

	return (arrChoiceName[Choice - 1]);
}

void	PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n______________Round[" << RoundInfo.RoundNumber << "]_______________\n";
	cout << "Player1 Choice  : " << ChoicName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoicName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner    : " << RoundInfo.WinnerName << endl;
	cout << "_____________________________________\n\n";
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return (enWinner::Player1);
	else if (ComputerWinTimes > Player1WinTimes)
		return (enWinner::Computer);
	else
		return (enWinner::Draw);
}

stGameResults	FillGameResults(short GameRound, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRound = GameRound;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.Winner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.Winner);

	return (GameResults);
}

stGameResults	PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;

	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound <" <<  GameRound << "> Begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return (FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes));
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (int i = 1; i <= NumberOfTabs; i++)
		t += "\t";

	return (t);
}

void ShowGameOverScreen()
{
	cout << Tabs(3) << "_____________________________________\n\n";
	cout << Tabs(3) << "         G A M E   O V E R\n";
	cout << Tabs(3) << "_____________________________________\n";
}

void	PrintFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(3) << "_____________________________________\n";
	cout << Tabs(3) << "Number Of  Rounds : " << GameResults.GameRound << endl;
	cout << Tabs(3) << "Player1 Win Times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(3) << "Computer Win Times: " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times        : " << GameResults.DrawTimes << endl;
	cout << Tabs(3) << "Game Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(3) << "_____________________________________\n";

}

void	StartGame()
{
	char PlayAgin = 'Y';

	do
	{

		stGameResults GameResults = PlayGame(ReadHowManyRound());
		ShowGameOverScreen();
		PrintFinalGameResults(GameResults);

		cout << "\nDo You Want To Play Again Y/N ? ";
		cin >> PlayAgin;

	} while (PlayAgin == 'Y' || PlayAgin == 'y');
}

