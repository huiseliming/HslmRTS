// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"
#include "RTSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARTSPlayerPawn::ARTSPlayerPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	MoveSpeed = 1.f;
	RotateSpeed = 1.f;
	InitialRotator = FRotator(-70.f,0.f,0.f);
	ZoomSpeed = 1.f;
	MinTargetArmLength = 500.f;
	MaxTargetArmLength = 10000.f;
	TargetArmLength = 5000.f;;
	bEnableRotate = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComp);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);

	CameraSpringArm->TargetArmLength = 3800.f;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->SetRelativeRotation(InitialRotator);
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bEnableCameraRotationLag = true;
}

// Called when the game starts or when spawned
void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.f));
}

// Called every frame
void ARTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController && PlayerController->IsLocalController())
	{
		if(bEnableRotate)
		{
			float MouseDeltaX,MouseDeltaY;
			PlayerController->GetInputMouseDelta(MouseDeltaX,MouseDeltaY);
			FRotator Rotator = CameraSpringArm->GetRelativeRotation();
			CameraSpringArm->SetRelativeRotation(FRotator(
                FMath::Clamp(Rotator.Pitch + MouseDeltaY * DeltaTime * RotateSpeed * 128.f,-80.f,-10.f),
                Rotator.Yaw + MouseDeltaX * DeltaTime * RotateSpeed * -256.f,
                0.f));
		}
		else
		{
			FVector2D MouseLocation;
			if (PlayerController->GetMousePosition(MouseLocation.X,MouseLocation.Y))
			{
				FIntVector ViewportSize;
				PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
				if (MouseLocation.X < 20 ||  MouseLocation.X > ViewportSize.X - 20)
				{
					const float RTSViewportTargetDirection = MouseLocation.X < ViewportSize.X / 2 ? -1 : 1;
					MoveRight(RTSViewportTargetDirection * DeltaTime);
				}
				if (MouseLocation.Y < 20 ||  MouseLocation.Y > ViewportSize.Y - 20)
				{
					const float RTSViewportTargetDirection = MouseLocation.Y < ViewportSize.Y / 2 ? -1 : 1;
					MoveForward(RTSViewportTargetDirection * DeltaTime);
				}
			}
			CameraSpringArm->TargetArmLength = FMath::FInterpTo(CameraSpringArm->TargetArmLength, TargetArmLength, DeltaTime, 3.f);
		}
	}
}

void ARTSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// BindAction
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetRotate"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::RotateStart);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetRotate"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::RotateEnd);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetResetRotate"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::RotateReset);

	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseLeftClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseLeftBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseLeftClick"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseLeftBtnReleased);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseRightClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseRightBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseRightClick"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseRightBtnReleased);
	// BindAction
	PlayerInputComponent->BindAxis(TEXT("RTSViewTargetZoomIn"), this, &ARTSPlayerPawn::ZoomIn);
}

void ARTSPlayerPawn::OnMouseLeftBtnPressed()
{
	
}

void ARTSPlayerPawn::OnMouseLeftBtnReleased()
{
	
}

void ARTSPlayerPawn::OnMouseRightBtnPressed()
{
	
}

void ARTSPlayerPawn::OnMouseRightBtnReleased()
{
	
}

void ARTSPlayerPawn::MoveForward(float Value)
{
	AddActorLocalOffset(FVector::CrossProduct(FVector::UpVector, Value * Camera->GetRightVector()) * MoveSpeed * (CameraSpringArm->TargetArmLength));
}

void ARTSPlayerPawn::MoveRight(float Value)
{
	AddActorLocalOffset(Value * Camera->GetRightVector() * MoveSpeed * (CameraSpringArm->TargetArmLength));
}

void ARTSPlayerPawn::RotateStart()
{
	bEnableRotate = true;
}

void ARTSPlayerPawn::RotateEnd()
{
	bEnableRotate = false;
}

void ARTSPlayerPawn::RotateReset()
{
	CameraSpringArm->SetRelativeRotation(InitialRotator);
}

void ARTSPlayerPawn::ZoomIn(float Value)
{
	const float NewTargetArmLength = Value * ZoomSpeed * TargetArmLength / 8;
	TargetArmLength = FMath::Clamp(TargetArmLength + NewTargetArmLength, MinTargetArmLength, MaxTargetArmLength);;
}
