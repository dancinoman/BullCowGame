#pragma once
#include "fBullCowGame.h"
#include <map>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TMap std::map


fBullCowGame::fBullCowGame() {Reset();}

using Fstring = std::string;
using int32 = int;

void fBullCowGame::Reset()
{

	
	int32 MAX_TRIES = GetMaxTries();//Maximum tries depends on the word lenght
	MyMaxTries = MAX_TRIES;//This value is used to end the game if the maximum tries is reached
	MyCurrentTry = 1;
	GuessMatch = false;
	
	return;
}

void fBullCowGame::GetWordByLenght(int32 LenghtToTry)
{
	//Select the right amount of the containers size
	TMap<int32, int32>  ArraySelect{ { 3,10 },{ 4,10 },{ 5,10 },{ 6,6 },{ 7,4 } };
	
	//Initiate time for a random Word in array
	std::srand(time(NULL));
	int32 RandIndex = rand() % ArraySelect[LenghtToTry];

	TMap<int32, FString> WordChoosed{ {3, Lenght3[RandIndex]}, {4, Lenght4[RandIndex]}, { 5, Lenght5[RandIndex] },{ 6, Lenght6[RandIndex] },{ 7, Lenght7[RandIndex] } };
	
	 const FString HIDDEN_WORD = WordChoosed[LenghtToTry];
	 MyHiddenWord = HIDDEN_WORD;

	 
}


int32 fBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32>  MaxRatio{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return MaxRatio[MyHiddenWord.length()];
}
int32 fBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

int32 fBullCowGame::ScoreGame()
{	
	   if (IsGameWon())
	   {
    		score += (50 * MyHiddenWord.length()) / GetCurrentTry();
		
	   }
	   else
	   {
		   score += 0;
	   }
	return score;
}

bool fBullCowGame::IsGameWon(){return GuessMatch;}
FString fBullCowGame::HiddenWord(){return MyHiddenWord;}
int32 fBullCowGame::GetHiddenWordLenght() const {return MyHiddenWord.length();}



bool fBullCowGame::IsIsogram(Fstring Word) const
{
	//treat and 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);// Mixed case
		if (LetterSeen[Letter]) 
		{ 
			return false; 
		} else {
			LetterSeen[Letter] = true;
		}
		
	}
	return true;
}

bool fBullCowGame::IsLowercase(Fstring Word) const
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

//recieves a VALID guess icriments turns, and returns count

FBullCowCount fBullCowGame::SubmitValidGuess(Fstring Guess)
{

	

	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length();

	//loop through all letters in the hidden word
	
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLenght; GChar++)
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// compare letters against the guess
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; //increment Bull
				}
				else
				{
					BullCowCount.Cows++; //Increment Cow
				}
				// if they match bulls if they're in the same place
			}
		}
	}

	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		GuessMatch = true;
	}
	else
	{
		GuessMatch = false;
	}

	
	return BullCowCount;
}

EGuessStatus fBullCowGame::CheckGuessValidity(Fstring Guess) const 
{
	if (!IsIsogram(Guess))//if the guess isn't an isogram return an error
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))//if the guess isn't all lower case 
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLenght())	//if guess lenght is wrong return error
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
	//otherwise return OK
}

ELenghtStatus fBullCowGame::CheckLenghtValidity(int32 LenghtToTry) const
{
		if ((LenghtToTry < 3) || (LenghtToTry > 7))
		{
			return ELenghtStatus::Not_good_range;
		}
		else
		{
			return ELenghtStatus::OK;
		}
}



