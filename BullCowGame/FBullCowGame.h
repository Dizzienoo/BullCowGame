#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//All Values Initialised to Zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	NOT_ISO,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

class FBullCowGame
{
public:
	FBullCowGame(); //Constructor

	int32 GetMinLength() const;
	int32 GetMaxLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	void SetRandomWord(int32);

	void Reset(); //TODO: make a more rich return value
	bool IsGameWon() const;
	EGuessStatus CheckGuessValid(FString) const;

	//Counts Bulls and Cows and INcreases Try #, assumes valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};


