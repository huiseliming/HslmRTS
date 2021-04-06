// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameModeBase.h"


#include "RTSHUD.h"
#include "RTSPlayerController.h"
#include "RTSPlayerPawn.h"

ARTSGameModeBase::ARTSGameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerPawn::StaticClass();
	HUDClass = ARTSHUD::StaticClass();
}
