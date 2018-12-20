#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
	FBullCowGame::Reset();
}

//Getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	bIsGameWon = false;
	
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;	
	int32 WordLength = GetHiddenWordLenght();
	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j])
			{
				if (i == j) // if they are in the same place
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

	if (BullCowCount.Bulls == WordLength)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letters words as isograms
	if (Word.length() <= 1) { return true; }

	//setup our map
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; } 
		else { LetterSeen[Letter] = true; }		
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
