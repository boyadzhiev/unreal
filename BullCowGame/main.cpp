/* This is the console executable, that makes us of the BullCow class.
This acts as the view in MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// functuion prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();

		PlayGame();

		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // exit the application
}

// play a single game to completion
void PlayGame()
{
	
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	FText Guess = "";

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries))
	{
		Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSummary();

	return;
}

void PrintIntro()
{	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n\n";

	std::cout << "         .e$$$$e.\n";
	std::cout << "       e$$$$$$$$$$e\n";
	std::cout << "      $$$$$$$$$$$$$$\n";
	std::cout << "     d$$$$$$$$$$$$$$b\n";
	std::cout << "     $$$$$$$$$$$$$$$$\n";
	std::cout << "    4$$$$$$$$$$$$$$$$F\n";
	std::cout << "    4$$$$$$$$$$$$$$$$F\n";
	std::cout << "     $$$\" \"$$$$\" \"$$$\n";
	std::cout << "     $$F   4$$F   4$$\n";
	std::cout << "     '$F   4$$F   4$\"\n";
		std::cout << "      $$   $$$$   $P\n";
	std::cout << "      4$$$$$\"^$$$$$%\n";
		std::cout << "       $$$$F  4$$$$\n";
	std::cout << "        \"$$$ee$$$\"\n";
	std::cout << "        . *$$$$F4\n";
	std::cout << "         $     .$\n";
	std::cout << "         \"$$$$$$\"\n";
	std::cout << "          ^$$$$\n\n";


	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letter.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}

	}
	while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	
	return Guess;
}

// ask player to play again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done, you won the game in " << (BCGame.GetCurrentTry() - 1) << " tries.\n\n";
	}
	else
	{
		std::cout << "You lost, better luck next time!\n\n";
	}
}