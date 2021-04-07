// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RTSPlayerState.h"

ARTSPlayerState::ARTSPlayerState()
{
	PlayerIndex = -1;
	ControlMask = 0;
	TeamIndex = -1;
	LocalTeamMask = 0;
}

void ARTSPlayerState::Initialize(uint32 PlayerIndex, uint32 TeamIndex)
{
	this->PlayerIndex = PlayerIndex;
	ControlMask = 1 << PlayerIndex;
	this->TeamIndex = TeamIndex;
}

void ARTSPlayerState::AddControl(uint32 PlayerIndex)
{
	ControlMask |= 1 << PlayerIndex;
}

void ARTSPlayerState::RemoveControl(uint32 PlayerIndex)
{
	ControlMask &= ~(1 << PlayerIndex);
}

bool ARTSPlayerState::HasControl(uint32 PlayerIndex)
{
	return 0 != ((1 << PlayerIndex) | ControlMask);
}

void ARTSPlayerState::SetLocalTeamMask(uint32 TeamMask)
{
	LocalTeamMask = TeamMask;
}

void ARTSPlayerState::AddPlayerToLocalTeam(uint32 PlayerIndex)
{
	LocalTeamMask |= 1 << PlayerIndex;
}

void ARTSPlayerState::RemovePlayerToLocalTeam(uint32 PlayerIndex)
{
	LocalTeamMask &= ~(1 << PlayerIndex);
}

bool ARTSPlayerState::IsTeammate(uint32 PlayerIndex)
{
	return 0 != ((1 << PlayerIndex) | LocalTeamMask);
}
