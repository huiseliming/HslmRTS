// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RTSPlayerPawn.h"
#include "EngineUtils.h"
#include "HslmRTS.h"
#include "UnitBase.h"
#include "Gameplay/RTSHUD.h"
#include "Gameplay/RTSPlayerController.h"
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
	InitialRotator = FRotator(-70.f, -90.f, 0.f);
	ZoomSpeed = 1.f;
	MinTargetArmLength = 500.f;
	MaxTargetArmLength = 10000.f;
	TargetArmLength = 5000.f;;
	bEnableRotate = false;

	bIsSelecting = false;
	bIsShiftPressed = false;

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
	if(RTSPlayerController && RTSPlayerController->IsLocalController())
	{
		if (!bIsSelecting)
		{
			UpdateTransformTick(DeltaTime);
		}
	}
}

void ARTSPlayerPawn::UpdateTransformTick(float DeltaTime)
{
	if(bEnableRotate)
	{
		float MouseDeltaX,MouseDeltaY;
		RTSPlayerController->GetInputMouseDelta(MouseDeltaX,MouseDeltaY);
		FRotator Rotator = CameraSpringArm->GetRelativeRotation();
		CameraSpringArm->SetRelativeRotation(FRotator(
            FMath::Clamp(Rotator.Pitch + MouseDeltaY * DeltaTime * RotateSpeed * 128.f,-80.f,-10.f),
            Rotator.Yaw + MouseDeltaX * DeltaTime * RotateSpeed * -256.f,
            0.f));
		return;
	}
	FVector2D MouseLocation;
	if (RTSPlayerController->GetMousePosition(MouseLocation.X,MouseLocation.Y))
	{
		FIntVector ViewportSize;
		RTSPlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
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

void ARTSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// BindAction
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetRotate"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::RotateStart);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetRotate"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::RotateEnd);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetResetRotate"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::RotateReset);

	PlayerInputComponent->BindAction(TEXT("RTSMouseLeftButton"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseLeftBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSMouseLeftButton"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseLeftBtnReleased);
	PlayerInputComponent->BindAction(TEXT("RTSMouseRightButton"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseRightBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSMouseRightButton"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseRightBtnReleased);
	PlayerInputComponent->BindAction(TEXT("RTSKeyboardShiftButton"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnKeyboardShiftBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSKeyboardShiftButton"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnKeyboardShiftBtnReleased);

	// BindAction
	PlayerInputComponent->BindAxis(TEXT("RTSViewTargetZoomIn"), this, &ARTSPlayerPawn::ZoomIn);
}

void ARTSPlayerPawn::PossessedBy(AController* NewController)
{
	RTSPlayerController = Cast<ARTSPlayerController>(NewController);
}

void ARTSPlayerPawn::UnPossessed()
{
	RTSPlayerController = nullptr;
}

void ARTSPlayerPawn::OnMouseLeftBtnPressed()
{
	check(RTSPlayerController);
	RTSPlayerController->GetHUD<ARTSHUD>()->DoSelectStart();
	bIsSelecting = true;
}

void ARTSPlayerPawn::OnMouseLeftBtnReleased()
{
	check(RTSPlayerController);
	RTSPlayerController->GetHUD<ARTSHUD>()->DoSelectFinish();
	bIsSelecting = false;
}

void ARTSPlayerPawn::OnMouseRightBtnPressed()
{
	check(RTSPlayerController);
	if (bIsShiftPressed)
	{
		if (RTSPlayerController->GetHUD<ARTSHUD>()->GetPreselectActors().Num() < 1)
		{
			// TODO: MoveToActor
			return;
		}
		FHitResult HitResult;
		if(RTSPlayerController->GetHitResultUnderCursor(ECC_RTSMovementTraceChannel, false, HitResult))
		{
			for (AActor* SelectedActor : RTSPlayerController->GetHUD<ARTSHUD>()->GetSelectedActors())
			{
				AUnitBase* Unit = Cast<AUnitBase>(SelectedActor);
				if (Unit)
				{
					Unit->PushOrder(MakeShared<FMoveToLocationOrder>(HitResult.Location));
				}
			}
		}
	}else{
		if (RTSPlayerController->GetHUD<ARTSHUD>()->GetPreselectActors().Num() < 1)
		{
			// TODO: MoveToActor
			return;
		}
		FHitResult HitResult;
		if(RTSPlayerController->GetHitResultUnderCursor(ECC_RTSMovementTraceChannel, false, HitResult))
		{
#ifdef WITH_EDITOR
			AActor* HitActor = HitResult.GetActor();
			if (HitActor != nullptr)
			{
				UE_LOG(LogHslmRTS, Log, TEXT("Mouse RightBtn clicked on Actor %s"), *HitActor->GetName());
			}
#endif
			for (AActor* SelectedActor : RTSPlayerController->GetHUD<ARTSHUD>()->GetSelectedActors())
			{
				AUnitBase* Unit = Cast<AUnitBase>(SelectedActor);
				if (Unit)
				{
					Unit->MoveToLocation(HitResult.Location);
				}
			}
		}
	}
}

void ARTSPlayerPawn::OnMouseRightBtnReleased()
{

}

void ARTSPlayerPawn::OnKeyboardShiftBtnPressed()
{
	bIsShiftPressed = true;
}

void ARTSPlayerPawn::OnKeyboardShiftBtnReleased()
{
	bIsShiftPressed = false;
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
