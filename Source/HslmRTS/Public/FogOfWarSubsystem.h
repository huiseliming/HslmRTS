// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FogOfWarSubsystem.generated.h"


class URTSAgentComponent;


/**
 *
 */
UCLASS()
class HSLMRTS_API UFogOfWarSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual	void Deinitialize() override;
	void AddRTSAgent(URTSAgentComponent* RTSAgent);
	void RemoveRTSAgent(URTSAgentComponent* RTSAgent);
	TArray<URTSAgentComponent*>& GetRTSAgents();

	FIntVector WorldLocationToWorldTile(FVector WorldLocation);

	int32 GetWorldTileIndex(int32 X, int32 Y){ return X + Y * GetTileWorldSize();}
	int32 GetWorldHeightLevel(int32 X, int32 Y){ return GetWorldHeightLevel(GetWorldTileIndex(X,Y));}
	int32 GetWorldHeightLevel(int32 Index){ return WorldTiles[Index] & 0xFFFF; }

	bool IsBlock(int32& X, int32& Y)
	{
		return (WorldTiles[GetWorldTileIndex(X, Y)] & (1 << 31)) != 0;
	}
	
	bool HasVision(int32& OriginX, int32& OriginY, int32& TargetX, int32& TargetY)
	{
		return !IsBlock(TargetX,TargetY) && GetWorldHeightLevel(OriginX,OriginY) >= GetWorldHeightLevel(TargetX,TargetY);
	}
	
	int32 GetTileWorldSize(){ return TileWorldSize; }

	// Bit32 is Block flag, Low16Bit Is HeightLevel
	TArray<int32> WorldTiles;

	int32 TileWorldSize;
private:
	TArray<URTSAgentComponent*> RTSAgents;
};
