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

    const TCHAR HW[] = TEXT("cakes");
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
            return;
        }

    if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaingin!"), Lives);
            return;
        }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT ("No repeating letters, guess again.\n"));
        return;
    }

    // Remove Life
        --Lives;
        PrintLine(TEXT("You have lost a life!"));
    // Check if Lives > 0
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s.\n"), *HiddenWord);
        EndGame();
        return;
    }
    //Shows the player the number of bulls and cows
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word){

    // for each letter
    // Start at element[0]
    // Compare against the next letter
    // Until we reach [guess.Len() - 1]
    // if any are the same return false

    return true;
}