// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"
#include "HslmRTS.h"
#include "EngineUtils.h"
#include "RTSHUD.h"
#include "RTSPlayerController.h"
#include "UnitBase.h"
#include "RTSActor.h"
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


	bIsSelecting = false;

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
			UpdateUnderCursorPreselectActor();
			UpdateTransformTick(DeltaTime);
		}
	}
}

void ARTSPlayerPawn::UpdateUnderCursorPreselectActor()
{
	FHitResult HitResult;
	if(RTSPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		TArray<AActor*>& PreselectActorsRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetPreselectActorsRef();
		AActor* HitActor = HitResult.Actor.Get();
		if(HitActor && PreselectActorsRef.Num() == 1 && PreselectActorsRef[0] == HitActor)
		{
			return;
		}
		for (int32 i = 0; i < PreselectActorsRef.Num(); i++)
		{
			if(PreselectActorsRef[i] == HitActor)
			{
				if (i != 0)
				{
					PreselectActorsRef.Swap(0,i);
				}
			}
			else
			{
				// OnUnpreselected(PreselectActors[i]);
			}
		}
		PreselectActorsRef.SetNum(1);
		if(PreselectActorsRef[0] != HitActor)
		{
			//OnPreselected(HitActor);
			PreselectActorsRef[0] = HitActor;
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

	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseLeftClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseLeftBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseLeftClick"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseLeftBtnReleased);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseRightClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerPawn::OnMouseRightBtnPressed);
	PlayerInputComponent->BindAction(TEXT("RTSViewTargetMouseRightClick"), EInputEvent::IE_Released, this, &ARTSPlayerPawn::OnMouseRightBtnReleased);
	
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
	bIsSelecting = true;
	RTSPlayerController->GetHUD<ARTSHUD>()->SetDrawSelectBox(true);
	FVector2D& FirstPointRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetFirstPointRef();
	RTSPlayerController->GetMousePosition(FirstPointRef.X, FirstPointRef.Y);
}

void ARTSPlayerPawn::OnMouseLeftBtnReleased()
{
	check(RTSPlayerController);
	FVector2D& FirstPointRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetFirstPointRef();
	FVector2D& SecondPointRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetSecondPointRef();
	if ((FirstPointRef - SecondPointRef).SizeSquared() < 100.f)
	{
		DoSingleSelect();
	}else
	{
		DoBoxSelect();
	}
	bIsSelecting = false;
	RTSPlayerController->GetHUD<ARTSHUD>()->SetDrawSelectBox(false);
}

void ARTSPlayerPawn::OnMouseRightBtnPressed()
{

}

void ARTSPlayerPawn::OnMouseRightBtnReleased()
{

}

void ARTSPlayerPawn::DoSingleSelect()
{
	TArray<AActor*>& PreselectActorsRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetPreselectActorsRef();
	if (PreselectActorsRef.IsValidIndex(0))
	{
		ARTSActor* RTSActor = Cast<ARTSActor>(PreselectActorsRef[0]);
		if(RTSActor)
		{
			SelectedActors.Empty();
			SelectedActors.Add(RTSActor);
			FocusedActor = RTSActor;
			UE_LOG(LogHslmRTS, Log, TEXT("SingleSelect %s"), *FocusedActor->GetName());
			return;
		}
		AUnitBase* Unit = Cast<AUnitBase>(PreselectActorsRef[0]);
		if(Unit)
		{
			SelectedActors.Empty();
			SelectedActors.Add(Unit);
			FocusedActor = Unit;
			UE_LOG(LogHslmRTS, Log, TEXT("SingleSelect %s"), *FocusedActor->GetName());
			return;
		}
	}
}

void ARTSPlayerPawn::DoBoxSelect()
{
	TArray<AActor*>& PreselectActorsRef = RTSPlayerController->GetHUD<ARTSHUD>()->GetPreselectActorsRef();
	SelectedActors = PreselectActorsRef;
	for (auto& SelectedActor : SelectedActors)
	{
		UE_LOG(LogHslmRTS, Log, TEXT("BoxSelect %s"), *SelectedActor->GetName());
	}
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
