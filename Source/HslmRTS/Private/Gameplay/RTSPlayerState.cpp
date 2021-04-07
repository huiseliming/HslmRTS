// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RTSPlayerState.h"

ARTSPlayerState::ARTSPlayerState()
{
	PlayerIndex = -1;
	ControlMask = 0;
	TeamIndex = -1;
	LocalTeamMask = 0;
}

void ARTSPlayerState::Initialize(uint32 InPlayerIndex, uint32 InTeamIndex)
{
	PlayerIndex = InPlayerIndex;
	ControlMask = 1 << InPlayerIndex;
	TeamIndex = InTeamIndex;
}

void ARTSPlayerState::AddControl(uint32 InPlayerIndex)
{
	ControlMask |= 1 << InPlayerIndex;
}

void ARTSPlayerState::RemoveControl(uint32 InPlayerIndex)
{
	ControlMask &= ~(1 << InPlayerIndex);
}

bool ARTSPlayerState::HasControl(uint32 InPlayerIndex)
{
	return 0 != ((1 << InPlayerIndex) | ControlMask);
}

void ARTSPlayerState::SetLocalTeamMask(uint32 TeamMask)
{
	LocalTeamMask = TeamMask;
}

void ARTSPlayerState::AddPlayerToLocalTeam(uint32 InTeamIndex)
{
	LocalTeamMask |= 1 << InTeamIndex;
}

void ARTSPlayerState::RemovePlayerToLocalTeam(uint32 InTeamIndex)
{
	LocalTeamMask &= ~(1 << InTeamIndex);
}

bool ARTSPlayerState::IsTeammate(uint32 InTeamIndex)
{
	return 0 != ((1 << InTeamIndex) | LocalTeamMask);
}
