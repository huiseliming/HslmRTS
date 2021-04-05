// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RTSSubsystem.h"
#include "GameFramework/Pawn.h"
#include "RTSPlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AUnitBase;
class ARTSPlayerController;

UCLASS()
class HSLMRTS_API ARTSPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARTSPlayerPawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSPlayerPawn")
	USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSPlayerPawn")
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSPlayerPawn")
	UCameraComponent* Camera;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UpdateTransformTick(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	UFUNCTION()
	void OnMouseLeftBtnPressed();
	//
	UFUNCTION()
	void OnMouseLeftBtnReleased();
	//
	UFUNCTION()
    void OnMouseRightBtnPressed();
	//
	UFUNCTION()
    void OnMouseRightBtnReleased();
	
	int32  bIsSelecting;
	
	UPROPERTY()
	ARTSPlayerController* RTSPlayerController;
	
public:
	// ViewTarget Move Rotate Zoom BEGIN
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	UFUNCTION()
	void RotateStart();
	UFUNCTION()
	void RotateEnd();
	UFUNCTION()
	void RotateReset();
	UFUNCTION()
	void ZoomIn(float Value);
	
public:
	//Editor Property
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float MoveSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float RotateSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	FRotator InitialRotator;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float ZoomSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float MaxTargetArmLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float MinTargetArmLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSPlayerPawn")
	float TargetArmLength;
	
	
private:
	bool bEnableRotate;
	// ViewTarget Move Rotate Zoom END
};
