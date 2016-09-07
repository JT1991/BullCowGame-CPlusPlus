#pragma once
#include "fBullCowGame.h"
#include <map>
#define TMap std::map //redefiniton to keep to unreal 4 engine syntax.

FBullCowGame::FBullCowGame(){ Reset();}//Default constructor

//Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,9}, {6,14}, {7,19} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(){
	const FString HIDDEN_WORD = "publish";//this MUST be an isogram!
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	//if the guess is not an isogram 
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} 
	//if guess not lowercase
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	//if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Incorrect_Length;
	}
	//if the guess has a number
	else if (false) {
		return EGuessStatus::No_Numbers_Allowed;
	}
	//otherwise return ok
	else {
		return EGuessStatus::OK;
	}
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

bool FBullCowGame::IsIsogram(FString Word) const{
	//treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	//setup our map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		//if letter is in map
		if (LetterSeen[Letter]) {
			return false; //we do NOT have an isogram
		}
		else {
			//add letter to map
			LetterSeen[Letter] = true;
		}
	}
	return true;// for example in cases where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))//if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
