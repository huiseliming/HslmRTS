// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HslmRTSFunctionLibrary.generated.h"

class ARTSGameModeBase;
class ARTSHUD;
class ARTSPlayerController;

/**
 *
 */
UCLASS()
class HSLMRTS_API UHslmRTSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSGameModeBase* GetRTSGameModeBase(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSHUD* GetRTSHUD(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSPlayerController* GetRTSPlayerController(const UObject* WorldContextObject);
	
};

