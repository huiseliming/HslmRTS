// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

class AUnitBase;

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

	TArray<AActor*>& GetPreselectActorsRef() { return PreselectActors; }
	FVector2D& GetFirstPointRef() { return FirstPoint; }
	FVector2D& GetSecondPointRef() { return SecondPoint; }
	void SetDrawSelectBox(bool IsDraw);

	UPROPERTY()
	TArray<AActor*> PreselectActors;

private:
	bool bIsDrawSelectBox;

	FVector2D FirstPoint;
	FVector2D SecondPoint;
public:
	void GetUnitsInSelectBox(const FVector2D& InFirstPoint, const FVector2D& InSecondPoint, TArray<AActor*>& OutUnits);
};
