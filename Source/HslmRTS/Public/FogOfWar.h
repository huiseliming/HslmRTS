﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogOfWar.generated.h"

class UFogOfWarSubsystem;
class ARTSWorldVolume;

struct FAgentCache
{
	FAgentCache() : VisibleCounter(0){ }
	void AddAgent(){ VisibleCounter++; }
	void RemoveAgent() { VisibleCounter--; }
	bool IsVisible() const { return VisibleCounter > 0; }
	int32 VisibleCounter;
};

struct FRecursiveVisionContext
{
	UFogOfWarSubsystem* FogOfWarSubsystem;
	int32 OriginX;
	int32 OriginY;
	int32 MaxDepth;
};

UCLASS()
class HSLMRTS_API AFogOfWar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFogOfWar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void UpdateFogOfWar();
	void RecursiveVision(FRecursiveVisionContext& Context, int32 Depth, int32 Start, int32 End);

	void Initialize();
	void Cleanup();
	int16 CalculateWorldHeightLevelAtLocation(const FVector2D WorldLocation);
	// FogOfWar Texture BEGIN
	// the texture   
	UPROPERTY()
	UTexture2D* FogOfWarTexture;
	uint8* FogOfWarTextureBuffer;
	uint32* FogOfWarTextureBufferSize;
	FUpdateTextureRegion2D FogOfWarTextureUpdateRegion;

	UPROPERTY()
	UTexture2D* FogOfWarUpscaleTexture;
	uint8* FogOfWarUpscaleTextureBuffer;
	uint32* FogOfWarUpscaleTextureBufferSize;
	FUpdateTextureRegion2D FogOfWarUpscaleTextureUpdateRegion;

	// FogOfWar resolution 
	FIntVector FogOfWarTextureResolution;
	FIntVector FogOfWarUpscaleTextureResolution;

	
	// FogOfWar Texture END



	//Tile info BEGIN

	void WorldLocationToTileXY(FVector InWorldLocation, int32 TileX, int32 TileY);

	int32 GetWorldTileIndex(int32 X, int32 Y) const { return X + Y * GetTileXResolution();}
	int32 GetWorldHeightLevel(int32 X, int32 Y){ return FogOfWarTiles[GetWorldTileIndex(X,Y)] & 0xFFFF;}
	bool IsBlock(int32& X, int32& Y){ return (FogOfWarTiles[GetWorldTileIndex(X, Y)] & (1 << 31)) != 0; }
	bool HasVision(int32& OriginX, int32& OriginY, int32& TargetX, int32& TargetY)
	{
		return !IsBlock(TargetX,TargetY) && GetWorldHeightLevel(OriginX,OriginY) >= GetWorldHeightLevel(TargetX,TargetY);
	}
	
	int32 GetTileXResolution() const { return FogOfWarTileResolution.X; }


	

	// The size of tile 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FogOfWar")
	float TileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FogOfWar")
	ARTSWorldVolume* RTSWorldVolume;
	
	FIntVector FogOfWarTileResolution;

	FVector OriginCoordinate;
	// world center 
	FVector WorldCenter;
	
	// Bit32 is Block flag, Low16Bit Is HeightLevel
	TArray<uint32> FogOfWarTiles;

	// Cache for tiles current has agents;
	TArray<FAgentCache> TileAgentCache;

};

