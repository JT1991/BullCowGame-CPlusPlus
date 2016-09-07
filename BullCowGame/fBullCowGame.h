/* The game logic (no view code or direct user interaction)
The game is a simple word guess game based on Mastermind*/

#pragma once
#include <string>
#include <map>
#define TMap std::map

//To make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Length,
	Non_Alphabetical,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame(); //constructor
	//Getters
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	FString GetHiddenWord() const;
	int32 GetGameDifficulty() const;

	//Setters
	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	void SetDifficulty(int);

private:
	//see constuctor for implementation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	int32 GameDifficulty = 1;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	bool IsAlphabetical(FString) const;
	FString GetNewHiddenWord();

	//ISOGRAM LIST
	//TODO make list for each letter word and allow 
	//user to pick letter length instead of difficulty.
	TMap <int32, FString> BeginnerIsgogramList{//4 letters
		{ 0,"ache" },{ 1,"aged" },{ 2,"acts" },{ 3,"back" },
		{ 4,"bail" },{ 5,"bead" },{ 6,"byte" },{ 7,"cafe" },
		{ 8,"city" },{ 9,"debt" },{ 10,"dust" },{ 11,"epic" },
		{ 12,"exit" },{ 13,"facts" },{ 14,"hack" },
		{ 15,"jury" },{ 16,"lane" },{ 17,"lamb" },{ 18,"shut" },
		{ 19,"smug" },{ 20,"tear" },{ 21,"time" },
	};
	TMap <int32, FString> EasyIsogramList{ //5-6 letters
		{0, "after"}, {1, "chokes"}, {2, "author"},
		{3, "ground"}, {4, "black"}, {5, "horse"},
		{6, "guild"}, {7, "faces"}, {8, "facet"},
		{9, "cards"}, {10, "olden"}, {11, "plants"},
		{12, "planet"}, {13, "dunce"}, {14, "stream"},
		{15, "waiter"}, {16, "twice"}, {17, "thrice"},
		{18, "sights"}, {19, "formed"}, {20, "parent"},
	};

	TMap <int32, FString> MediumIsogramList{ // 7 - 8
		{0, "shocked"}, {1, "choking"}, {2, "playing"},
		{3, "personal"}, {4, "bankrupt"}, {5, "disturb"},
		{6, "document"}, {7, "republic"}, {8, "disgrace"},
		{9, "hospital"}, {10, "destroy"}, {11, "flouride"},
		{12, "trample"}, {13, "infamous"}, {14, "complain"},
		{15, "farsight"}, {16, "judgment"}, {17, "mistake"},
		{18, "consider"}, {19, "vouched"}, {20, "parents"},
	};

	TMap <int32, FString> HardIsogramList{ // 9 - 10 letter words
		{0, "conjugate"}, {1, "artichokes"}, {2, "authorizes"},
		{3, "background"}, {4, "bankruptcy"}, {5, "binoculars"},
		{6, "blackhorse"}, {7, "atmosphere"}, {8, "boyfriends"},
		{9, "campground"}, {10, "clothespin"}, {11, "complaints"},
		{12, "conjugated"}, {13, "despicably"}, {14, "desirably"},
		{15, "downstream"}, {16, "dumbwaiter"}, {17, "duplicates"},
		{18, "farsighted"}, {19, "formidable"}, {20, "godparents"},
	};
};
