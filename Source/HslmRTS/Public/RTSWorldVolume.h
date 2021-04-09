// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "RTSWorldVolume.generated.h"

/**
 * 
 */
UCLASS()
class HSLMRTS_API ARTSWorldVolume : public AVolume
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	// Set reasonable default values.

public:
	void Initialize();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTSWorldVolume")
	float TileSize;
	
	
};
