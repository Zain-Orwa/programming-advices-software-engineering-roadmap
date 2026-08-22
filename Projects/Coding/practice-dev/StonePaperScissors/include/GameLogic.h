#include "GameStruct.h"
#include <iostream>
#include <cstdlib>
#include <string>

using  namespace std;

int RandomNumber(int From, int To);
short ReadHowManyRound();
enGameChoice	ReadPlayer1Choice();
enGameChoice GetComputerChoice();
enWinner WhoWonTheRound(stRoundInfo RoundInfo);
string	WinnerName(enWinner Winner);
string ChoicName(enGameChoice Choice);
void	PrintRoundResults(stRoundInfo RoundInfo);
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes);
stGameResults	FillGameResults(short GameRound, short Player1WinTimes, short ComputerWinTimes, short DrawTimes);
stGameResults	PlayGame(short HowManyRound);
string Tabs(short NumberOfTabs);
void ShowGameOverScreen();
void	PrintFinalGameResults(stGameResults GameResults);
void	StartGame();
