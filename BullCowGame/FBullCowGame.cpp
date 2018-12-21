/**/
#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { FBullCowGame::Reset(); } // default constructor

//Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	
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
		return EGuessStatus::Not_Lowercase; 
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
