/*This is the console executable that makes use of the bullCow class.
THis acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCow class.
*/
#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
void GetGameDifficulty();
FText GetValidGuess();
bool AskToReplay();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse across plays.

//entry point
int main() 
{
	bool bWantsToReplay = false;
	do
	{
		PrintIntro();
		GetGameDifficulty();
		PlayGame();
		bWantsToReplay = AskToReplay();
	}
	while (bWantsToReplay);
	return 0; // exit application
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls & Cows\n";
	std::cout << std::endl;
	std::cout << "    /|           /|" << std::endl;
	std::cout << "    ((__,-'''-,__))" << std::endl;
	std::cout << "     `--)~   ~(--` " << std::endl;
	std::cout << "    .-'(       )`-," << std::endl;
	std::cout << "    `~~`d>   <b`~~`" << std::endl;
	std::cout << "        |     |    " << std::endl;
	std::cout << "        (6___6)    " << std::endl;
	std::cout << "         `---`     " << std::endl;
	std::cout << "Can you guess the isogram I'm thinking of?\n" << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	//moved from print intro because print intro showed wordlength
	//picked at start. This shows wordlength after difficulty picked
	std::cout << "\nThe hidden isogram has " << BCGame.GetHiddenWordLength() << " letters. Good luck!\n";
	std::cout << std::endl;
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while game NOT won
	//and there are still trys remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess();
		
		//Submit valid guess to game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

//designed to set the game difficulty, which determines which isogram list the game chooses.
void GetGameDifficulty()
{
	FText PlayerDifficulty = "";
	int32 GameDifficulty;

	//Prompt for difficulty 1=Easy, 2=Medium, 3=Hard
	do {
		std::cout << "\nSet the difficulty of the game.\n";
		//BEGINNER
		std::cout << "1 = " << "Beginner (4 letter words)\n";
		//EASY
		std::cout << "2 = ";
		std::cout << "Easy (5 to 6 letter words)\n";
		//MEDIUM
		std::cout << "3 = ";
		std::cout << "Medium (7 to 8 letter words)\n";
		//HARD
		std::cout << "4 = ";
		std::cout << "Hard (9 to 12 letter words)\n";
		std::cout << "\n";

		//get and consume input and set difficulty to input.
		std::getline(std::cin, PlayerDifficulty);	//Get console input	for difficulty.
		GameDifficulty = std::stoi(PlayerDifficulty); //turn console input string into a sanitized integer
	} while (GameDifficulty < 1 || GameDifficulty > 4); //while first character value != 1, 2, 3, 4

	BCGame.SetDifficulty((int)GameDifficulty);	//set difficulty to requested.
}

//loop continually until user inputs valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Guess a word: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess is not an isogram. Please only input words without repeating letters.\n\n";
			break;
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please input " << BCGame.GetHiddenWordLength();
			std::cout << " letter isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use lowercase.\n\n";
			break;
		case EGuessStatus::Non_Alphabetical:
			std::cout << "English alphabetical characters only.\n\n";
			break;
		default:
			//assume guess valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors.
	return Guess;
}

bool AskToReplay()
{
	std::cout << "Do you want to play again with the same word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - YOU WIN! \n";
		std::cout << "You won in ";
		std::cout << BCGame.GetCurrentTry() - 1;
		std::cout << " out of " << BCGame.GetMaxTries() << " attemps! Your final score is: ";
		std::cout << ((BCGame.GetGameDifficulty() * (BCGame.GetMaxTries() - BCGame.GetCurrentTry() + 2)) * 10);
	}
	else {
		std::cout << "You Lose!\n";
		std::cout << "Hidden isogram was " << BCGame.GetHiddenWord();
		std::cout << std::endl;
	}
}
