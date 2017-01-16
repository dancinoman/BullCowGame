/* The game logic 
The game is a simple guess wprd based on mastermind
*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialised to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum  class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Blank_Space_Calculated,
	Not_Lowercase,
	

};

enum class ELenghtStatus
{
	Invalid_Status,
	Not_good_range,
	OK
};


class fBullCowGame 
{
public:
	fBullCowGame(); // contructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	int32 MaxTriesRatio();
	int32 ScoreGame();
	
	
	bool IsGameWon();
	FString HiddenWord();

	EGuessStatus CheckGuessValidity(FString) const ; 
	ELenghtStatus CheckLenghtValidity(int32) const;
	
	void Reset(); 
	void GetWordByLenght(int32);

	//counts bulls & cows, and increasing try# assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

	

	

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	int32 score;
	FString MyHiddenWord;
	FString Lenght3[10] = {"car", "dog", "cat", "air", "who", "bet", "own", "not", "say", "job"};
	FString Lenght4[10] = { "stop", "save", "wife", "talk", "many", "sail", "vote", "like", "post", "more" };
	FString Lenght5[10] = { "under", "sound", "about", "among", "party", "child", "large", "shift", "month", "right" };
	FString Lenght6[6] = {"income", "planet", "hourly", "polite", "mastic", "filter"};
	FString Lenght7[4] = { "central", "include", "picture", "another"};
	bool GuessMatch = false;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

