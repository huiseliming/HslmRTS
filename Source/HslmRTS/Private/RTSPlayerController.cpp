// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "RTSPlayerPawn.h"
#include "Engine/World.h"

ARTSPlayerController::ARTSPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	// RTSViewTargetPawn = nullptr;
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
	bShowMouseCursor = true;
}

void ARTSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
