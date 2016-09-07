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
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
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
		case EGuessStatus::No_Numbers_Allowed:
			std::cout << "No numbers!\n\n";
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
	}
	else {
		std::cout << "You Lose!\n";
	}
}
