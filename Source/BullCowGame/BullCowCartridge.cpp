// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms =  GetValidWords(Words);

    SetupGame();
    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    HiddenWord.Len();

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else if (PlayerInput.IsNumeric())
    {
        int32 newInput = FCString::Atoi(*PlayerInput);;
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
            PrintLine(TEXT("Sorry, that was not a valid input.\nPlease press 1 for a hint."));
            if (NumberOfHints >= 1)
            {  
                PrintLine(TEXT("Press 2 to see your hints."));
            }
            PrintLine(TEXT("Or type in a guess."));
        }
    }
    else //Check PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }  
}

void UBullCowCartridge::SetupGame()
{
     // Welcoming Our Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false; 
    NumberOfHints = 0;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
   // PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
    PrintLine(TEXT("You have %i Lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt Player for Guess


    const TCHAR HW[] = TEXT("cakes");

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter key to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("You have %i lives left."), Lives);

    PrintLine(TEXT("You can press 1 to get a hint."));
    
    if(NumberOfHints > 1)
    {
        PrintLine(TEXT("You can press 2 to see your hints."));
    }

    PrintLine(TEXT("Or you can guess again."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <=10 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{ 
    FBullCowCount Count;

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;

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