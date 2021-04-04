// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSSubsystem.h"

void URTSSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void URTSSubsystem::Deinitialize()
{

}

void URTSSubsystem::AddToRTSSubsystem(AUnitBase* Uint)
{
	WorldUintBaseSet.Add(Uint);
}

void URTSSubsystem::RemoveFromRTSSubsystem(AUnitBase* Uint)
{
	WorldUintBaseSet.Remove(Uint);
}
