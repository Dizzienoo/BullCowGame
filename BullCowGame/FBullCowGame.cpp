#include "FBullCowGame.h"
#include <map>
#include <cstdlib>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMinLength() const { return 3; }

int32 FBullCowGame::GetMaxLength() const { return 8; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}

void FBullCowGame::SetRandomWord(int32 WordLength)
{
	TMap<int32, FString> WorkingDic;
	switch (WordLength)
	{
		case 3:
			WorkingDic = TMap<int32, FString>
			{
				{1, "jab"}, 
				{2, "dog"}, 
				{3, "cat"},
				{4, "log"},
				{5, "bra"},
				{6, "boy"},
				{7, "nob"}
			};
			break;
		case 4:
			WorkingDic = TMap<int32, FString>
			{
				{1, "girl"},
				{2, "arch"},
				{3, "feud"},
				{4, "dock"},
				{5, "lime"},
				{6, "numb"},
				{7, "quiz"}
			};
			break;
		case 5:
			WorkingDic = TMap<int32, FString>
			{
				{1, "alert"},
				{2, "bacon"},
				{3, "haste"},
				{4, "upset"},
				{5, "orbit"},
				{6, "march"},
				{7, "elbow"}
			};
			break;
		case 6:
			WorkingDic = TMap<int32, FString>
			{
				{1, "gambit"},
				{2, "direct"},
				{3, "normal"},
				{4, "planet"},
				{5, "quartz"},
				{6, "sacked"},
				{7, "ravish"}
			};
			break;
		case 7:
			WorkingDic = TMap<int32, FString>
			{
				{1, "agonise"},
				{2, "joinery"},
				{3, "earplug"},
				{4, "glamour"},
				{5, "novelty"},
				{6, "obesity"}
			};
			break;
		case 8:
			WorkingDic = TMap<int32, FString>
			{
				{1, "campfire"},
				{2, "handsome"},
				{3, "morality"},
				{4, "wackiest"},
				{5, "yourself"},
				{6, "flagship"},
				{7, "keyboard"}
			};
			break;
	}
	int32 Random = rand();
	int32 WordNum = Random % WorkingDic.size();
	MyHiddenWord = WorkingDic[WordNum];
	return;
}

bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries
	{
		{3,7}, {4,10}, {5,12}, {6,14}, {7,16}
	};
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "planet";
	bIsGameWon = false;
	//MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValid(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (!IsLowerCase(Guess))
	{

		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (!IsIsogram(Guess))
	{
		
		return EGuessStatus::NOT_ISO;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//Recieves a Valid Guess, increments turn, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//Increment Turn Number
	MyCurrentTry++;
	//Setup Return Variable
	FBullCowCount BullCowCount;
	//Loop Through all letters in the Hidden Word
	int32 MyHiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < MyHiddenWordLength; i++)
	{
		//Loop through all the letters in the Guess
		for (int32 j = 0; j < MyHiddenWordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (j == i)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		//Compare all letters against the hidden word
	//Return the Bull Cow Count
	if (BullCowCount.Bulls >= MyHiddenWordLength) { bIsGameWon = true; }
	return BullCowCount;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (char Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


bool FBullCowGame::IsIsogram(FString Guess) const
{
	//Create Map
	TMap <char, bool> LetterSeen;
	//Get the Hidden Word Length
	int32 HiddenWordLength = GetHiddenWordLength();
	//Run through each letter
	for (char Letter : Guess)
	{
		//If we have seen it
		if (LetterSeen[Letter] == true)
		{
			//Return False
			return false;
		}
		//Otherwise, mark it as seen
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}