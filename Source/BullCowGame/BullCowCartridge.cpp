// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!")); // Remove later, added it up here for testing purposes - Cassandra
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
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long. \n You have lost!"), HiddenWord.Len());
                EndGame();
            }
        
        }
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
    Lives = 4;
    bGameOver = false; 

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess. \n Press enter to continue...")); // Prompt Player for Guess

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter key to play again."));
}