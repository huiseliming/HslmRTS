// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWarSubsystem.h"

void UFogOfWarSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UFogOfWarSubsystem::Deinitialize()
{

}

void UFogOfWarSubsystem::AddRTSAgent(URTSAgentComponent* RTSAgent)
{
	check(RTSAgents.Contains(RTSAgent));
	RTSAgents.Add(RTSAgent);
}

void UFogOfWarSubsystem::RemoveRTSAgent(URTSAgentComponent* RTSAgent)
{
	const int32 RemovedNum = RTSAgents.Remove(RTSAgent);
	check(RemovedNum);
}
