// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RTSSubsystem.generated.h"

class AUnitBase;

/**
 *
 */
UCLASS()
class HSLMRTS_API URTSSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

	void AddToRTSSubsystem(AUnitBase* Uint);
	void RemoveFromRTSSubsystem(AUnitBase* Uint);
	
	// All unit will save to set  
	UPROPERTY()
	TSet<AUnitBase*> WorldUintBaseSet;
	
};
