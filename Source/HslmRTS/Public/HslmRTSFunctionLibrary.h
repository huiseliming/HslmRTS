// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HslmRTSFunctionLibrary.generated.h"

class ARTSGameModeBase;
class ARTSHUD;
class ARTSPlayerController;

/**
 *
 */
UCLASS()
class HSLMRTS_API UHslmRTSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSGameModeBase* GetRTSGameModeBase(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSHUD* GetRTSHUD(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Hslm|RTSFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ARTSPlayerController* GetRTSPlayerController(const UObject* WorldContextObject);



	// Gaussian Blur BEGIN
	
	// Calculates a 1d gaussian bell shaped kernel
    static TArray<float> ComputeGaussianKernel(const int inRadius, const float inWeight)
    {
        int mem_amount = (inRadius*2)+1;
    	TArray<float> GKernel;
    	GKernel.SetNum(mem_amount);
    	
        float twoRadiusSquaredRecip = 1.0 / (2.0 * inRadius * inRadius);
        float sqrtTwoPiTimesRadiusRecip = 1.0 / (sqrt(2.0 * PI) * inRadius);
        float radiusModifier = inWeight;
    
        // Create Gaussian Kernel
        int r = -inRadius;
        float sum = 0.0f;
        for (int i = 0; i < mem_amount; i++)
        {
            float x = r * radiusModifier;
            x *= x;
            float v = sqrtTwoPiTimesRadiusRecip * exp(-x * twoRadiusSquaredRecip);
            GKernel[i] = v;
               
            sum+=v;
            r++;
        }
        // Normalize distribution
        float div = sum;
        for (int i = 0; i < mem_amount; i++)
            GKernel[i] /= div;
        return GKernel;
    }
	// Gaussian Blur END
};
