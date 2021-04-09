// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSWorldVolume.h"

#include "FogOfWar.h"
#include "Components/BrushComponent.h"
#include "Kismet/GameplayStatics.h"

void ARTSWorldVolume::BeginPlay()
{
}

void ARTSWorldVolume::Initialize()
{
	AFogOfWar* FogOfWarActor;
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, AFogOfWar::StaticClass(), Actors);
	if(!Actors.IsValidIndex(0)){
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FogOfWarActor = GetWorld()->SpawnActor<AFogOfWar>(AFogOfWar::StaticClass(),GetActorLocation(),GetActorRotation(),ActorSpawnParameters);
	}else{
		FogOfWarActor = Cast<AFogOfWar>(Actors[0]);
	}
	UBrushComponent* RTSWorldBrushComponent = GetBrushComponent();
	const FBoxSphereBounds RTSWorldBounds = RTSWorldBrushComponent->CalcBounds(RTSWorldBrushComponent->GetComponentTransform());
	FogOfWarActor->Cleanup();
	FogOfWarActor->Initialize(RTSWorldBounds);
	
}
