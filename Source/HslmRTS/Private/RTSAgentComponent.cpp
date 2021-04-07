// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSAgentComponent.h"
#include "FogOfWarSubsystem.h"

// Sets default values for this component's properties
URTSAgentComponent::URTSAgentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bAgentEnabled = true;
	VisionRadius = 500;
	HeightLevel = 0;
}


// Called when the game starts
void URTSAgentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetSubsystem<UFogOfWarSubsystem>()->AddRTSAgent(this);
}

void URTSAgentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetSubsystem<UFogOfWarSubsystem>()->RemoveRTSAgent(this);
}

// Called every frame
void URTSAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTSAgentComponent::EnableAgent(bool bEnable /*= true*/)
{
	bAgentEnabled =	bEnable;
}

void URTSAgentComponent::DisableAgent()
{
	bAgentEnabled = false;
}

bool URTSAgentComponent::IsAgentEnabled() const
{
	return bAgentEnabled;
}

void URTSAgentComponent::SetVisionRadius(int32 NewVisionRadius)
{
	VisionRadius = NewVisionRadius;
}

void URTSAgentComponent::SetHeightLevel(int32 NewHeightLevel)
{
	HeightLevel = NewHeightLevel;
}
