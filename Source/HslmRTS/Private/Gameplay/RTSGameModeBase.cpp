// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RTSGameModeBase.h"


#include "Gameplay/RTSHUD.h"
#include "Gameplay/RTSPlayerController.h"
#include "Gameplay/RTSPlayerPawn.h"

ARTSGameModeBase::ARTSGameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerPawn::StaticClass();
	HUDClass = ARTSHUD::StaticClass();
}
