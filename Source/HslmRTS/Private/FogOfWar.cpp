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

void AFogOfWar::UpdateFogOfWar()
{
	// https://www.albertford.com/shadowcasting/#Quadrant
	auto FogOfWarSubsystem = GetWorld()->GetSubsystem<UFogOfWarSubsystem>();
	for (auto Agent : FogOfWarSubsystem->GetRTSAgents())
	{
		FRecursiveVisionContext Context;
		Context.MaxDepth = Agent->VisionRadius;
		// Context.OriginX = ;
		// Context.OriginY = ;
		RecursiveVision(Context,1, -1, 1);
	}
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

void AFogOfWar::RecursiveVision(FRecursiveVisionContext& Context, int32 Depth, int32 Start, int32 End)
{
	int32 y = Context.OriginY + Depth;
	for (int32 i = Start; i <= End; i++)
	{
		int32 x = Context.OriginX + i;
		if (!HasVision(Context.OriginX, Context.OriginY, x, y))
		{
			int32 NewStart = ((((Depth + 1) * Start) * 2 ) + Depth) / (Depth * 2);
			int32 NewEnd = ((((Depth + 1) * i) * 2 ) + Depth) / (Depth * 2);
			RecursiveVision(Context, Depth + 1, NewStart, NewEnd);
			Start = i;
		}
	}
	int32 NextDepth = Depth + 1;
	if (NextDepth < Context.MaxDepth)
	{
		int32 NewStart = ((((Depth + 1) * Start) * 2 ) + Depth) / (Depth * 2);
		int32 NewEnd = ((((Depth + 1) * End) * 2 ) + Depth) / (Depth * 2);
		RecursiveVision(Context, NextDepth, NewStart, NewEnd); 
	}
}
#define Floor FloorToInt
void AFogOfWar::WorldLocationToTileXY(FVector InWorldLocation, int32 TileX, int32 TileY)
{
	FVector WorldLocation(InWorldLocation.X,InWorldLocation.Y,0.f);
	FVector RTSWorldOriToWorldLocation = WorldLocation - (GetActorLocation() - FVector(TileNumber / 2 * TileSize));
	
	int32 X = FMath::Floor(RTSWorldOriToWorldLocation.X / TileSize);
	int32 Y = FMath::Floor(RTSWorldOriToWorldLocation.Y / TileSize);
	//return FIntVector(X,Y,GetWorldHeightLevel([Y * TileNumber + X]));
}
#undef Floor
