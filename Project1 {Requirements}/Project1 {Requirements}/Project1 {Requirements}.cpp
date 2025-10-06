#include <iostream>
#include<cmath>
#include<string.h>
#include<cstdlib>
using namespace std;

enum MyEnum_choice
{
	Stone=1,Paper=2,Scissors=3

};

enum MyEnum_winner
{
	Player1=1,Computer=2,Draw=3

};

struct MyStruct_RoundInfo
{
	short Roundnumber = 0;
	MyEnum_choice Player1_choice;
	MyEnum_choice Computer_choice;
	MyEnum_winner Winner;
	string WinnerName;
};

struct MyStruct_GameResults
{
	short GameRounds = 0;
	short Player1TimesWin = 0;
	short ComputerTimesWin = 0;
	short DrawTimes = 0;
	MyEnum_winner GameWinner;
	string Name_Winner = " ";
};

short HowManyRounds() {
	short Game_Round = 1;
	do
	{
		cout << "\n How Many Rounds you want to Play? (1 To 10): \n";
		cin >> Game_Round;

	} while (Game_Round<1 || Game_Round>10);

	return Game_Round;
}

int RandomNumber(int From, int To) {
	int RandNumber = 0;
	RandNumber = rand() % (To - From + 1) + From;
	return RandNumber;
}

MyEnum_choice GetComputerChoice () {
	return (MyEnum_choice)RandomNumber(1,3);
} 

string ChoiceName(MyEnum_choice Choice) {
	string arrChoiceName[3] = { "Stone","Paper","Scissors" };
	return arrChoiceName[Choice - 1];
}

string WinnerName(MyEnum_winner Winner) {
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

MyEnum_choice ReadPlayer1Choice() {
	short Choice;
	do
	{
		cout << "\nYour Choice :[1]:Stone, [2]:Paper, [3]:Scissors ??" << endl;
		cin >> Choice;

	} while (Choice<1||Choice>3);
	return (MyEnum_choice)Choice;
}

MyEnum_winner WhoWonTheRound(MyStruct_RoundInfo Round_info) {
	if (Round_info.Player1_choice==Round_info.Computer_choice)
	{
		return MyEnum_winner::Draw;
	}

	switch (Round_info.Player1_choice) {
	case MyEnum_choice::Stone :
		if (Round_info.Computer_choice==MyEnum_choice::Paper)
		{
			return MyEnum_winner::Computer;
		}
		break;

	case MyEnum_choice::Paper:
		if (Round_info.Computer_choice==MyEnum_choice::Scissors)
		{
			return MyEnum_winner::Computer;
		}
		break;

	case(MyEnum_choice::Scissors):
		if (Round_info.Computer_choice==MyEnum_choice::Stone)
		{
			return MyEnum_winner::Computer;
		}
		break;

	}
	return MyEnum_winner::Player1;
}

MyEnum_winner WhoWonTheGame(short Player1TimesWin, short ComputerTimesWin) {
	if (Player1TimesWin>ComputerTimesWin)
	{
		return MyEnum_winner::Player1;
	}
	else if (Player1TimesWin<ComputerTimesWin)
	{
		return MyEnum_winner::Computer;
	}
	else
	{
		return MyEnum_winner::Draw;
	}
}

void SetScreenColor(MyEnum_winner winner) {
	switch (winner)
	{
		case
		MyEnum_winner::Player1:
			system("color 2F");
			break;
			case
			MyEnum_winner::Computer:
				system("Color 4F");
				cout << "\a";
				break;
			default:
				system("Color 6F");
				break;
	}
}

void PrintRoundResults(MyStruct_RoundInfo RoundInfo) {
	cout << "\n____________ Round [" << RoundInfo.Roundnumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1_choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.Computer_choice) << endl;
	cout << "Round Winner :[ " << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;

}

MyStruct_GameResults PlayGame(short HowManyRounds)
{
	MyStruct_RoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.Roundnumber = GameRound;
		RoundInfo.Player1_choice = ReadPlayer1Choice();
		RoundInfo.Computer_choice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == MyEnum_winner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == MyEnum_winner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return { HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}
 
void ShowGameOverScreen()
{

	cout << "=============================\n" << endl;
	cout << "     +++  GAME OVER +++       " << endl;
	cout << "\n \n=============================" << endl; 
	cout << endl;

	
	cout << "   (Stone_Paper_Scissors)" << endl;
	cout << endl;
	cout << "Better luck next time!" << endl;
	cout << endl;

} 

void ShowFinalGameResults(MyStruct_GameResults GameResults) {

	cout << "\n____________________[ Final Game Results]____________________\n";
	cout << "Total Rounds Played       : " << GameResults.GameRounds << endl;
	cout << "Player1 Wins             : " << GameResults.Player1TimesWin << endl;
	cout << "Computer Wins            : " << GameResults.ComputerTimesWin << endl;
	cout << "Draws                    : " << GameResults.DrawTimes << endl;
	cout << "----------------------------------------\n";
	cout << "Overall Game Winner      : " << GameResults.Name_Winner << endl;
	cout << "________________________________________________________________\n\n";

	SetScreenColor(GameResults.GameWinner);
}

void ResetScreen() {
	system("cls");
	system("Color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();  // Clear the screen before starting a new game.
		MyStruct_GameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << "\nDo you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));  // Seed random number generator.
	StartGame();  // Start the game.
	return 0;  
}

