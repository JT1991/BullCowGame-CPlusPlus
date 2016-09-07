#pragma once
#include "fBullCowGame.h"
#include <map>
#include <time.h>
#define TMap std::map //redefiniton to keep to unreal 4 engine syntax.

FBullCowGame::FBullCowGame(){ Reset();}//Default constructor

//Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length();}
int32 FBullCowGame::GetGameDifficulty() const { return GameDifficulty; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

FString FBullCowGame::GetHiddenWord() const
{
	return MyHiddenWord;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	return MyMaxTries;
}

//set difficulty value
void FBullCowGame::SetDifficulty(int Difficulty)
{
	GameDifficulty = Difficulty;
}

void FBullCowGame::Reset()
{
	//TODO further improvement, there could be a map of words, with more than one word per length.
	MyHiddenWord = GetNewHiddenWord();
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength()) {//if the guess length is wrong
		return EGuessStatus::Incorrect_Length;
	}
	else if (!IsAlphabetical(Guess)) {//// if the guess has non-alphabet characters
		return EGuessStatus::Non_Alphabetical;
	} else if (!IsIsogram(Guess)) {//if the guess is not an isogram 
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) {	//if guess not lowercase
		return EGuessStatus::Not_Lowercase;
	} else {//otherwise return ok
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const 
{
	//treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;//setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case			 
		if (LetterSeen[Letter]) {//if letter is in map
			return false; //we do NOT have an isogram
		}
		else {
			//add letter to map
			LetterSeen[Letter] = true;
		}
	}
	return true;// for example in cases where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const 
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsAlphabetical(FString Guess) const
{
	for (int32 GuessCNo = 0; GuessCNo < (int32)Guess.length(); GuessCNo++)
	{ //Alphabetical if guess is upper case A to Z or lower case A to Z.
		if ((Guess[GuessCNo] >= 'A' && Guess[GuessCNo] <= 'Z') || (Guess[GuessCNo] >= 'a' && Guess[GuessCNo] <= 'z')) {
			return true;
		}
	}
	return false;
}


//recieves a VALID guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	FBullCowCount BullCowCount;
	MyCurrentTry++;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		//compare letters against the guess
		for (int32 j = 0; j < WordLength; j++) {
			//if they match then
			if (Guess[i] == MyHiddenWord[j]) {
				// if in same place
				if (i == j) {
					//increment bulls
					BullCowCount.Bulls++;
				}
				else {
					//increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

FString FBullCowGame::GetNewHiddenWord()
{
	//get random integer based on time 
	srand(time(NULL));
	int32 Random = std::rand() % 20;

	//Give word based on difficulty
	if (GameDifficulty == 1) {//begginer
		MyMaxTries = 6;
		return BeginnerIsgogramList[Random];
	}
	else if (GameDifficulty == 2) {//easy
		MyMaxTries = 10;
		return EasyIsogramList[Random];
	}
	else if (GameDifficulty == 3) {//medium
		MyMaxTries = 15;
		return MediumIsogramList[Random];
	}
	else {
		MyMaxTries = 20;
		return HardIsogramList[Random];
	}
}

