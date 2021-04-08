// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar.h"


#include "FogOfWarSubsystem.h"
#include "RTSAgentComponent.h"


// Sets default values
AFogOfWar::AFogOfWar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFogOfWar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*
oooo@oooo->(x)
ooo**oooo
oo****ooo
o******oo
********o
    I
    v(y)
*/
void AFogOfWar::UpdateFogOfWar()
{
	// auto FogOfWarSubsystem = GetWorld()->GetSubsystem<UFogOfWarSubsystem>();
	// for (auto Agent : FogOfWarSubsystem->GetRTSAgents())
	// {
	// 	FIntVector WorldTile = FogOfWarSubsystem->WorldLocationToWorldTile(Agent->GetComponentLocation());
	// 	for (int32 i = 0; i < Agent->VisionRadius; i++)
	// 	{
	// 		for (int32 j = 0 - Agent->VisionRadius; j < Agent->VisionRadius; j++)
	// 		{
	// 			int32 OriginX = WorldTile.X;
	// 			int32 OriginY = WorldTile.Y;
	// 			int32 TargetX = WorldTile.X + j;
	// 			int32 TargetY = WorldTile.Y + i;
	// 			if(FogOfWarSubsystem->HasVision(OriginX, OriginY, TargetX, TargetY)){
	// 				
	// 			}else{
	// 				
	// 			}
	// 		}
	// 	}
	// }
}

