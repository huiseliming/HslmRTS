// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"


#include "AIController.h"
#include "HslmRTS.h"
#include "RTSSubsystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetSubsystem<URTSSubsystem>()->AddToRTSSubsystem(this);
	//Cast<AAIController>(GetController())->ReceiveMoveCompleted.AddDynamic(this, &AUnitBase::OnReceiveMoveCompleted);
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AUnitBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Cast<AAIController>(NewController)->ReceiveMoveCompleted.AddDynamic(this, &AUnitBase::OnReceiveMoveCompleted);
}

void AUnitBase::UnPossessed()
{
	Super::UnPossessed();
}

void AUnitBase::MoveToLocation(FVector Goal)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Goal);
}

void AUnitBase::OnReceiveMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	TSharedPtr<IRTSOrder> Order = RTSOrderQueue.PopOrder();
	while (Order && !(*Order.Get())(this))
	{
		Order = RTSOrderQueue.PopOrder();
	}
	UE_LOG(LogHslmRTS, Log, TEXT("OnReceiveMoveCompleted"));
}

void AUnitBase::PushOrder(TSharedPtr<IRTSOrder> RTSOrder)
{
	RTSOrderQueue.PushOrder(RTSOrder);
	if(Cast<AAIController>(GetController())->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		TSharedPtr<IRTSOrder> Order = RTSOrderQueue.PopOrder();
		while (Order && !(*Order.Get())(this))
		{
			Order = RTSOrderQueue.PopOrder();
		}
	}
}

void AUnitBase::ExecuteOrder(TSharedPtr<IRTSOrder> RTSOrder)
{
	RTSOrderQueue.ClearOrder();
	(*RTSOrder.Get())(this);
}

