// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation\PathFollowingComponent.h"
#include "RTSOrder.h"
#include "GameFramework/Character.h"
#include "UnitBase.generated.h"


UCLASS()
class HSLMRTS_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	void MoveToLocation(FVector Goal);
	
	UFUNCTION()
	void OnReceiveMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
public:
	
	
	void PushOrder(TSharedPtr<IRTSOrder> RTSOrder);
	void ExecuteOrder(TSharedPtr<IRTSOrder> RTSOrder);

	FRTSOrderQueue RTSOrderQueue;
};
