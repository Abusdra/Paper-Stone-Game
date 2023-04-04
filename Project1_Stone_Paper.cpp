#include <iostream>
#include <string>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner{Player=1,Computer=2,Draw=3};
struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults {
	short GameRounds = 0;
	short PlayerWinTimes = 0;

	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
int RandomInRange(int from,int to) {
	return rand() % (to - from + 1) + 1;
}
string WinnerName(enWinner Winner) {
	string arr[3] = { "Player","Computer","No Winner" };
	return arr[Winner - 1];
}
enWinner WhoWinnerRound(stRoundInfo RoundInfo) {
	if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice) {
		return enWinner::Draw;
	}
	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}
string ChoiceName(enGameChoice GameChoice) {
	string arr[3] = { "Stone","Paper","Scissors" };
	return arr[GameChoice - 1];
}
void color(enWinner winner) {
	switch (winner)
	{
	case Player:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		cout << "\a";
		break;
	case Draw:
		system("color 6F");
		break;
	}
}
void PrintResultRound(stRoundInfo RoundInfo) {
	cout << "_____________Round [" << RoundInfo.RoundNumber << "]______________\n\n";
	cout << "Player   Choice :" << ChoiceName(RoundInfo.PlayerChoice)<<"\n";
	cout << "Computer Choice :" << ChoiceName(RoundInfo.ComputerChoice) << "\n";
	cout << "Winner          :" << RoundInfo.WinnerName << "\n\n____________________________________\n\n";
	color(RoundInfo.Winner);
}
enWinner WhoWinnerGame(short PlayWinners,short ComputerWinners) {
	if (PlayWinners > ComputerWinners)
		return enWinner::Player;
	else if (PlayWinners == ComputerWinners)
		return enWinner::Draw;
	else
		return enWinner::Computer;
}
stGameResults FillGameResult(short GameRounds,short PlayWinners,short ComouterWinners,short Draw) {
	stGameResults GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.PlayerWinTimes = PlayWinners;
	GameResult.ComputerWinTimes = ComouterWinners;
	GameResult.DrawTimes = Draw;
	GameResult.GameWinner = WhoWinnerGame(PlayWinners, ComouterWinners);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;
}
enGameChoice GetComputerChoice() {
	return enGameChoice(RandomInRange(1, 3));
}
enGameChoice ReadPlayerChoice() {
	int choice;
	do {
	cout << "Choice [1]:Stone [2]:Paper [3]:Scissors\n";
	cin >> choice;
	} while (choice > 3 || choice < 1);

	return (enGameChoice)choice;
}
stGameResults PlayGame(short GameRounds) {
	stRoundInfo RoundInfo;
	short PlayerWiners=0, ComputerWiners=0, Draw=0;
	for (int GameRound = 1; GameRound <= GameRounds; GameRound++) {
		cout << "\nRound[" << GameRound << "] begins :\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinnerRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
	
		if (RoundInfo.Winner == enWinner::Player) {
		PlayerWiners++;
	}

		else if (RoundInfo.Winner == enWinner::Computer) {
		ComputerWiners++;
		}

		else {
		Draw++;
		}

	PrintResultRound(RoundInfo);
}
	return FillGameResult(GameRounds, PlayerWiners, ComputerWiners, Draw);
}
short ReadRoundsTimes() {
	int n;
	do {
		cout << "Inter How Many Round You Wont To Play From 1 TO 10 ?\n";
		cin >> n;
	} while (n < 1 || n>10);
	return n;
}
void PrintResultGame(stGameResults GameResult) {
	color(GameResult.GameWinner);
	cout << "\t\t\t\t_______________________[Game Result]_______________________\n\n";
	cout << "\t\t\t\tGame Rounds        : " << GameResult.GameRounds << "\n";
	cout << "\t\t\t\tPlayer1 Win Times  : " << GameResult.PlayerWinTimes << "\n";
	cout << "\t\t\t\tComputer Win Times : " << GameResult.ComputerWinTimes << "\n";
	cout << "\t\t\t\tDraw Times         : " << GameResult.DrawTimes << "\n";
	cout << "\t\t\t\tFinal Winner       : " << GameResult.WinnerName << "\n\n";
	color(GameResult.GameWinner);
}
void PrintHeaderEnd() {
	cout << "\t\t\t\t___________________________________________________________\n\n";
	cout << " \t\t\t\t\t\t+++ G a m e  O v e r +++\n";
	cout << "\t\t\t\t___________________________________________________________\n\n";
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
void StartGame() {
	char again;
	do {
		ResetScreen();
		stGameResults GameResult = PlayGame(ReadRoundsTimes());
		PrintHeaderEnd();
		PrintResultGame(GameResult);
		cout << "You wont to play again Y | N \n";
		cin >> again;
	} while (again == 'y' || again == 'Y');

}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}
