/*This is the console executable, that makes use of the BullCow class. 
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For have logic see the FBullCowGame class.


*/
#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.h" 

using Ftext = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
void GameSettings();
void PrintGamesSummary();

bool AskToPlayAgain();
Ftext GetValidGuess();


fBullCowGame BCGame;// instantiate a new game

//the entry point for the application
int main()
{
	PrintIntro();

	bool bPlayAgain = false;
	do
	{
		
		PlayGame();

		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	BCGame.GetHiddenWordLenght();
	//introduce the game
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	
	std::cout << "          .=      ,    =.\n";
	std::cout << "    _  _/'/    )\,/,/(_ \\ \\\n";
	std::cout << "  `//-.|  (  ,\\)\//\)\/_   ) |\n";
	std::cout << "  //___\\   `\\\/\\/\/\\///'    /\n";
	std::cout << ",-""~`-._ `""--'_   `""""`  _ \`'""~-,_\n";
	std::cout << "\       `-.'_`.        .'_` \ ,-""~`-\n";
	std::cout << "`.__.-'`/   (-\\      /-) |-.__,'\n";
	std::cout << "  ||   |     \O) /^\   --  /\n";
	std::cout << "  ` \\  |       /   `\    /\n";
	std::cout << "     \\  \      /      `\ /\n";
	std::cout << "     `\\ `-.  /' .---.--.\\\n";
    std::cout << "       `\\/`~(, '()     ())\n";
	std::cout << "        /(O) \\  \\_,.-.,_)\n";
    std::cout << "       //  \\ `\'`______/\n";
    std::cout << "      / |  ||          \n";
	std::cout << "   __/' |__||\n";
    std::cout << "__/  \n";
	std::cout << "    \n";
	std::cout << "\n";
	std::cout << " \n";
	std::cout << "     \n";
	std::cout << "     \n";
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Cow indicates how many good letter(s). And Bull indicates the same thing but at the right place." << std::endl;
	
	
}

void PlayGame()
{  
	BCGame.Reset();

	GameSettings();

	int MaxTries = BCGame.GetMaxTries();
	
	//loop asking for guesses while the game is not won and still tres remaining
		while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess(); 

		//Submit valid guess to the game is and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";
	

		std::cout << std::endl;

	}

		PrintGamesSummary();

		return;
}

void PrintGamesSummary()
{
	

	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRADULATION!YOU WON THE GAME!\n";
		std::cout << "Your score is : " << BCGame.ScoreGame() << "\n";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!\n";
		std::cout << "The word I was thinking was '" << BCGame.HiddenWord() << "'";
		std::cout << std::endl;
	    std::cout << "Your score is : " << BCGame.ScoreGame() << "\n";
		std::cout << std::endl;
	}
	return;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n)? ";
	Ftext Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void GameSettings()
{
	int32 LenghtToTry;
	ELenghtStatus Status = ELenghtStatus::Invalid_Status;
	//repeat until goog range
	do {
		std::cout << "Which lenght do you want to try (3, 4, 5, 6 or 7)?";
		scanf("%d/%s", &LenghtToTry);
		std::cout << std::endl;
	
		Status = BCGame.CheckLenghtValidity(LenghtToTry);
		switch (Status)
		{
		     case ELenghtStatus::Not_good_range:
			   std::cout << "Please type a number between 3 and 7\n";
	    	 break;

		    default:
			   break;

		}

	} while (Status != ELenghtStatus::OK);

	BCGame.GetWordByLenght(LenghtToTry);
	std::cout << "Can you guess the word I'm thinking of?\n";
	int32 TriesLeft = BCGame.GetMaxTries();
	std::cout << "You have " << TriesLeft << " tries left.\n";
	std::cout << std::endl;
	return;
}


//loop continally the number until the user gives a valid guess
Ftext GetValidGuess ()
{

	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player
		int32 XTries = BCGame.GetCurrentTry();
		int32 TotalTries = BCGame.GetMaxTries();
		std::cout << "Try " << XTries<< "/" << TotalTries <<". Type your guessing word here: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lower case letter only\n\n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;

			default:
				//Assume the guess valid
				break;
		}
		
	} while (Status != EGuessStatus::OK); //Keep looping until get no error
	
	return Guess;
}


