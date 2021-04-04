// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSViewTargetPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HSLMRTS_API ARTSViewTargetPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARTSViewTargetPawn();

	//Editor Property
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float MoveSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float RotateSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	FRotator InitialRotator;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float ZoomSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float MaxTargetArmLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float MinTargetArmLength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Hslm|RTSViewTarget")
	float TargetArmLength;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSViewTarget")
	USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSViewTarget")
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hslm|RTSViewTarget")
	UCameraComponent* Camera;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	UFUNCTION()
	void RotateStart();
	UFUNCTION()
	void RotateEnd();
	UFUNCTION()
	void RotateReset();
	
private:
	bool bEnableRotate;
	
public:
	UFUNCTION()
	void ZoomIn(float Value);
	
};
