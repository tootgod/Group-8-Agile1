// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    HiddenWord.Len();

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }

    else //Check PlayerGuess
    {
        ProcessGuess(Input);
    }
    // Check if Isogram
    // Prompt to guess again
    // Check right number of characters
    // Prompt to guess again

    // Remove Life

    // Check if Lives > 0
    // If Yes, GuessAgain
    // Show Lives Left
    // If No, Show GameOever and HiddenWord
    // Prompt to Play Again, "Press Enter to Play Again?"
    // Check their Input
    // PlayAgain or Quit
    
}
void UBullCowCartridge::SetupGame()
{
     // Welcoming Our Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false; 

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt Player for Guess

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter key to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        else
        {
            --Lives;
            PrintLine(TEXT("You have lost a life!"));
            if(Lives > 0){
                if (Guess.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaingin!"), Lives);
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
        }
}