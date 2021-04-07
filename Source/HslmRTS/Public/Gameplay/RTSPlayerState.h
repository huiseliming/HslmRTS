// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HSLMRTS_API ARTSPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ARTSPlayerState();

	void Initialize(uint32 PlayerIndex,uint32 TeamIndex = -1);
	void AddControl(uint32 PlayerIndex);
	void RemoveControl(uint32 PlayerIndex);
	bool HasControl(uint32 PlayerIndex);

	void SetLocalTeamMask(uint32 TeamMask);
	void AddPlayerToLocalTeam(uint32 PlayerIndex);
	void RemovePlayerToLocalTeam(uint32 PlayerIndex);
	bool IsTeammate(uint32 PlayerIndex);
	
	uint32 TeamIndex;
	uint32 LocalTeamMask;
	
	uint32 ControlMask;
	uint32 PlayerIndex;
};
