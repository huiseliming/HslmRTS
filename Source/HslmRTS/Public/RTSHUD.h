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

	TArray<AActor*>& GetSelectedActors() { return SelectedActors; }
	const TArray<AActor*>& GetPreselectActors() { return PreselectedActors; }
	AActor* GetFocusedActor() const { return FocusedActor; }
	
	void UpdatePreselectedActorUnderCursor();
	void UpdatePreselectedActorsInBox();
	
	void DoSelectStart();
	void DoSelectFinish();
	void DoSingleSelect();
	void DoBoxSelect();

	void ClearPreselectActors();
	void ClearSelectedActors();
	void SelectSingleActor(AActor* Actor);
	void SelectActors(TArray<AActor*>& Actors);
	
	void OnActorSelected(AActor* Actor);
	void OnActorUnselected(AActor* Actor);
	void OnActorPreselected(AActor* Actor);
	void OnActorUnpreselected(AActor* Actor);

	
	UPROPERTY()
	TArray<AActor*> SelectedActors;
	UPROPERTY()
	AActor* FocusedActor;
	UPROPERTY()
	TArray<AActor*> PreselectedActors;


	int32 SelectedActorsCounter;
	int32 PreselectedActorsCounter;
	
private:
	bool bIsSelecting;

	FVector2D FirstPoint;
	FVector2D SecondPoint;
public:
	void GetUnitsInSelectBox(const FVector2D& InFirstPoint, const FVector2D& InSecondPoint, TArray<AActor*>& OutUnits);
};
