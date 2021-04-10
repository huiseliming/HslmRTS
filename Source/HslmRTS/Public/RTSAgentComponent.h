// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RTSAgentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HSLMRTS_API URTSAgentComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URTSAgentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// virtual void InitializeComponent() override;
	// virtual void UninitializeComponent() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// FogOfWar BEGIN

	UFUNCTION(BlueprintCallable, Category = "Hslm|RTSAgentComponent")
	void EnableAgent(bool bEnable = true);
	UFUNCTION(BlueprintCallable, Category = "Hslm|RTSAgentComponent")
	void DisableAgent();
	UFUNCTION(BlueprintCallable, Category = "Hslm|RTSAgentComponent")
	bool IsAgentEnabled() const;
	UFUNCTION(BlueprintCallable, Category = "Hslm|RTSAgentComponent")
	void SetVisionRadius(int32 NewVisionRadius);
	UFUNCTION(BlueprintCallable, Category = "Hslm|RTSAgentComponent")
	void SetHeightLevel(int32 NewHeightLevel);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTSAgentComponent")
	bool bAgentEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTSAgentComponent")
	int32 VisionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTSAgentComponent")
	int32 HeightLevel;


	TArray<int32>  CacheVisionTiles;
	FIntVector CacheAgentTile;
	
	// FogOfWar END
};
