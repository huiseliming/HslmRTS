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

	void Initialize(uint32 InPlayerIndex,uint32 InTeamIndex = -1);
	void AddControl(uint32 InPlayerIndex);
	void RemoveControl(uint32 InPlayerIndex);
	bool HasControl(uint32 InPlayerIndex);

	void SetLocalTeamMask(uint32 TeamMask);
	void AddPlayerToLocalTeam(uint32 InTeamIndex);
	void RemovePlayerToLocalTeam(uint32 InTeamIndex);
	bool IsTeammate(uint32 InTeamIndex);
	
	uint32 TeamIndex;
	uint32 LocalTeamMask;
	
	uint32 ControlMask;
	uint32 PlayerIndex;
};
