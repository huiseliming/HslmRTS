// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 *
 */
UCLASS()
class HSLMRTS_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARTSHUD();


	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;

	FVector2D& GetFirstPointRef() { return FirstPoint; }
	FVector2D& GetSecondPointRef() { return SecondPoint; }
	void SetDrawSelectBox(bool IsDraw);
	
	UPROPERTY()
    TArray<AActor*> CurrentInsideBoxActors;
	
private:
	bool bIsDrawSelectBox;

	FVector2D FirstPoint;
	FVector2D SecondPoint;

};
