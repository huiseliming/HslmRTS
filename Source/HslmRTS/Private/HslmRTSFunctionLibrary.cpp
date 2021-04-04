// Fill out your copyright notice in the Description page of Project Settings.


#include "HslmRTSFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ARTSGameModeBase* UHslmRTSFunctionLibrary::GetRTSGameModeBase(const UObject* WorldContextObject)
{
	return Cast<ARTSGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

ARTSHUD* UHslmRTSFunctionLibrary::GetRTSHUD(const UObject* WorldContextObject)
{
	return Cast<ARTSHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}

ARTSPlayerController* UHslmRTSFunctionLibrary::GetRTSPlayerController(const UObject* WorldContextObject)
{
	return Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}
