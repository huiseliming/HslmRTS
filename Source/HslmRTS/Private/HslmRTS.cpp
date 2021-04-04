// Copyright Epic Games, Inc. All Rights Reserved.

#include "HslmRTS.h"

#define LOCTEXT_NAMESPACE "FHslmRTSModule"

void FHslmRTSModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogHslmRTS, Log, TEXT("FHslmRTSModule Loaded"));
}

void FHslmRTSModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogHslmRTS, Log, TEXT("FHslmRTSModule Unload"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHslmRTSModule, HslmRTS)
DEFINE_LOG_CATEGORY(LogHslmRTS);
