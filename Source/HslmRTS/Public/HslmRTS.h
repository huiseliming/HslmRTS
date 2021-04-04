// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define ECC_RTSMovableTraceChannel ECollisionChannel::ECC_GameTraceChannel10

// Helper for display code file and line
#define UE__FUNC__ (FString(__FUNCTION__))
#define UE__LINE__ (FString::FromInt(__LINE__))
#define UE__FUNC__LINE__ (UE__FUNC__ + "(" + UE__LINE__ + ")")

class FHslmRTSModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FHslmRTSModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FHslmRTSModule>("HslmRTS");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("HslmRTS");
	}
};
DECLARE_LOG_CATEGORY_EXTERN(LogHslmRTS, Log, All);
