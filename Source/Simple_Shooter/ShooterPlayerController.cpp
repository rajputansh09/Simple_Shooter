// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay(); // Call the base class BeginPlay method

    HUD = CreateWidget(this, HUDClass); // Create an instance of the HUD widget
        
    if (HUD) // Check if the widget was created successfully
    {
        HUD->AddToViewport(); // Add the HUD widget to the viewport
    }   
     
}



void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner); // Call the base class implementation of GameHasEnded

    HUD->RemoveFromViewport(); // Remove the HUD widget from the viewport
    
    if (bIsWinner) // Check if the player is a winner
    {
        UUserWidget* WinScreen = CreateWidget<UUserWidget>(this, WinScreenClass); // Create an instance of the win screen widget
        if (WinScreen) // Check if the widget was created successfully
        {
            WinScreen->AddToViewport(); // Add the win screen widget to the viewport
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget<UUserWidget>(this, LoseScreenClass); // Create an instance of the lose screen widget
        if (LoseScreen) // Check if the widget was created successfully
        {
            LoseScreen->AddToViewport(); // Add the lose screen widget to the viewport
        }
    }

    
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay); // Set a timer to restart the level after the specified delay


}


