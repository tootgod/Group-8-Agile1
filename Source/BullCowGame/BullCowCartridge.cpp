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
    else if (Input.IsNumeric())
    {
        int32 newInput = FCString::Atoi(*Input);;
        if((newInput == 1) && (Lives > 1))
        {
            NumberOfHints ++;
            --Lives;
            PlayerHint(NumberOfHints);
        }
        else if (newInput == 2)
        {
            PlayerHint(NumberOfHints);
        }
        else if ((newInput == 1) && (Lives <= 1))
        {
            PrintLine(TEXT("Sorry, you do not have enough lives\nto get a hint."));
            PrintLine(TEXT("Please enter your final guess."));
            PrintLine(TEXT("Or press 2 to see your hints."));
            return;
        }
        else
        {
            PrintLine(TEXT("Sorry, that was not a valid input.\nPlease press 1 for a hint. \nPress 2 to see your hints."));
            PrintLine(TEXT("Or type in a guess."));
        }
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
    NumberOfHints = 0;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
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
            return;
        }
    if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining!"), Lives);
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

    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s.\n"), *HiddenWord);
        EndGame();
        return;
    }

    //Shows the player the number of bulls and cows
    PrintLine(TEXT("You have %i lives left."), Lives);
    PrintLine(TEXT("Hints are available for a life.\nPress 1 if you would like a new hint.")); 
    if (NumberOfHints > 0) 
    {
        PrintLine(TEXT("Press 2 if you want to see your hints."));
    }
    PrintLine(TEXT("Otherwise type in your next guess."));
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }           
        }  
    }
    
    return true;

}

void UBullCowCartridge::PlayerHint(int32 NumberOfHints)
{

    if(NumberOfHints > 0)
    {
        FString HintString = HiddenWord.Mid(0, NumberOfHints);
        PrintLine(TEXT("The first %i letters of the \nhidden word are: %s"), NumberOfHints, *HintString);
        PrintLine(TEXT("You have %i lives remaining.\nPlease type in your next guess."), Lives);
        if (Lives > 1)
        {
            PrintLine(TEXT("Or press 1 for another hint."));
        }
        return;
    }

    return;
}