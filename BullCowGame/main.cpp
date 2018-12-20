#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//contracts
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game
FBullCowGame BCGame;

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

	return 0;
}

// play the game
void PlayGame()
{
	
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	//std::cout << "Current Try: " << CurrentTry << std::endl;

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

	// TODO add a game summary
	return;
}

// introduce the game
void PrintIntro()
{	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";

	std::cout << "          /******\\       \n";
	std::cout << "         /        \\    \n";
	std::cout << "        |  *    *  |    \n";
	std::cout << "         \\   /\\   /     \n";
	std::cout << "          |      |      \n";
	std::cout << "            *||*        \n";
	

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