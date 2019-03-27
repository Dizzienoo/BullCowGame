#pragma once
#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintStart(int32 WORD_LENGTH);
void PlayGame();
void SetWordLength(int32, int32);
FText GetValidGuess();
void PrintBack(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;

//Application Entry Point
int main() 
{	
	int32 MIN_LENGTH = BCGame.GetMinLength();
	int32 MAX_LENGTH = BCGame.GetMaxLength();
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	bool bPlayAgain = true;
	do
	{
		//Play the Game's Intro
		PrintIntro();
		//Get Word Length
		SetWordLength(MIN_LENGTH, MAX_LENGTH);
		//Print Start
		PrintStart(WORD_LENGTH);
		//Run the Main Game Loop
		PlayGame();
		//Check if the User wants to play again
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain == true);
	return 0;
}

//Runs the Game Logic
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
			//Get the Guess
			Guess = GetValidGuess();
			//Repeat the guess back to them
			PrintBack(Guess);
			//Submit Valid Guess to Game
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			//Print the Number of Bulls and Cows
			std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
			std::cout << "Cows = " << BullCowCount.Cows << "\n" <<std::endl;
	}
	PrintGameSummary();
	return;
}

//Prints Game intro
void PrintIntro()
{
	std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
	std::cout << "Welcome to Bulls and Cows \n";
}

void SetWordLength(int32 MIN_LENGTH, int32 MAX_LENGTH)
{
	FText Input = "";
	bool correctNumber = false;
	do
	{
		std::cout << "Enter a number between " << MIN_LENGTH << " and " << MAX_LENGTH << ".";
		std::cout << std::endl;
		getline(std::cin, Input);
		int32 n = std::stoi(Input);
		if (n >= MIN_LENGTH && n <= MAX_LENGTH)
		{
			BCGame.SetRandomWord(n);
			correctNumber = true;
			std::cout << "Number set to " << Input;
			std::cout << std::endl;
		}
	} while (correctNumber == false);
}

void PrintStart(int32 WORD_LENGTH)
{
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

//Get Guess From the Player
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << "Try " << CurrentTry << " of " << MaxTries << ". Enter your guess: ";
		std::cout << std::endl;
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::NOT_ISO:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter a lowercase word." << std::endl;
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintBack(FText Guess)
{
	std::cout << std::endl;
	std::cout << "Your Guess is: " << Guess << std::endl;
}

void PrintGameSummary()
{
	//If the Guess is our Target
	if (BCGame.IsGameWon())
	{
		//We Have Won
		std::cout << "You Have Won" << std::endl;
	}
	else
	{
		//We Have Lost
		std::cout << "You Have Lost" << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?\nEnter Y for Yes and N for No" << std::endl;
	FText Response = "";
	bool Answer = false;
	bool Answered = false;
	while (Answered == false)
	{
		getline(std::cin, Response);
		if (Response[0] == 'Y' || Response[0] == 'y' || Response == "True" || Response == "true")
		{
			Answer = true;
			Answered = true;
		}
		else if (Response[0] == 'N' || Response[0] == 'n' || Response == "False" || Response == "false")
		{
			Answer = false;
			Answered = true;
		}
		else
		{
			std::cout << "I Did not understand, please enter Y for Yes and N for No" << std::endl;
		}
	}
	return Answer;
}