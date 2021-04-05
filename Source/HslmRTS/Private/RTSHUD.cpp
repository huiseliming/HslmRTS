// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "EngineUtils.h"
#include "HslmRTS.h"
#include "UnitBase.h"

ARTSHUD::ARTSHUD()
{
	bIsDrawSelectBox = false;
}

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ARTSHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	if(bIsDrawSelectBox)
	{
		GetOwningPlayerController()->GetMousePosition(SecondPoint.X, SecondPoint.Y);
		const float ScreenX = FirstPoint.X < SecondPoint.X ? FirstPoint.X : SecondPoint.X ;
		const float ScreenY = FirstPoint.Y < SecondPoint.Y ? FirstPoint.Y : SecondPoint.Y ;
		const float Width = FMath::Abs(SecondPoint.X - FirstPoint.X);
		const float Height = FMath::Abs(FirstPoint.Y - SecondPoint.Y);
		//GLog->Log(FString::Printf(TEXT("ScreenX: %f, ScreenY: %f, Width: %f, Height: %f"), ScreenX, ScreenY, Width, Height));
		DrawRect(FLinearColor(0.5,0.5,0.5,0.3), ScreenX, ScreenY, Width, Height);
		DrawLine(ScreenX, ScreenY, ScreenX +Width, ScreenY, FLinearColor::Gray);
		DrawLine(ScreenX + Width, ScreenY,ScreenX + Width, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX + Width, ScreenY + Height, ScreenX, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX, ScreenY + Height, ScreenX, ScreenY, FLinearColor::Gray);
		TArray<AActor*> OldPreselectActors;
		Swap(PreselectActors,OldPreselectActors);
		GetUnitsInSelectBox(FirstPoint, SecondPoint, PreselectActors);
		//GetActorsInSelectionRectangle(AUnitBase::StaticClass() ,FirstPoint, SecondPoint,PreselectActors,false ,false);
		PreselectActors.Sort();//[](AActor** A, AActor** B) mutable { return A < B; });
		Algo::Sort(PreselectActors,[](const AActor* A, const AActor* B) { return A < B; });
		if(PreselectActors.Num() == 0)
		{
			for (AActor* Actor : OldPreselectActors)
			{
				//OnRTSSelectionUnhovered.Broadcast(Actor);
				UE_LOG(LogHslmRTS, Log, TEXT("Unpreselect %s"), *Actor->GetName());
			}
		}else{
			int32 PreselectActorsIndex = 0;
			for (int32 i = 0; i < OldPreselectActors.Num(); i++)
			{
				while (PreselectActorsIndex < PreselectActors.Num()
					&& OldPreselectActors[i] > PreselectActors[PreselectActorsIndex])
				{
					//OnRTSSelectionHovered.Broadcast(PreselectActors[PreselectActorsIndex]);
					UE_LOG(LogHslmRTS, Log, TEXT("Preselect %s"), *PreselectActors[PreselectActorsIndex]->GetName());
					PreselectActorsIndex++;
				}
				if(PreselectActorsIndex >= PreselectActors.Num())
				{
					//OnRTSSelectionUnhovered.Broadcast(OldPreselectActors[i]);
					UE_LOG(LogHslmRTS, Log, TEXT("Unpreselect %s"), *OldPreselectActors[i]->GetName());
					continue;
				}
				if(OldPreselectActors[i] < PreselectActors[PreselectActorsIndex])
				{
					//OnRTSSelectionUnhovered.Broadcast(OldPreselectActors[i]);
					UE_LOG(LogHslmRTS, Log, TEXT("Unpreselect %s"), *OldPreselectActors[i]->GetName());
				}
				else if(OldPreselectActors[i] == PreselectActors[PreselectActorsIndex])
				{
					PreselectActorsIndex++;
				}
			}
			while (PreselectActorsIndex < PreselectActors.Num())
			{
				//OnRTSSelectionHovered.Broadcast(CurrentHoveredActors[PreselectActorsIndex]);
				UE_LOG(LogHslmRTS, Log, TEXT("Preselect %s"), *PreselectActors[PreselectActorsIndex]->GetName());
				PreselectActorsIndex++;
			}
		}
	}
}

void ARTSHUD::SetDrawSelectBox(bool IsDraw)
{
	bIsDrawSelectBox = IsDraw;
	if(IsDraw == false){
		for (int32 i = 0; i < PreselectActors.Num(); i++){
			//OnRTSSelectionUnhovered.Broadcast(PreselectActors[i]);
			UE_LOG(LogHslmRTS, Log, TEXT("Unpreselect %s"), *PreselectActors[i]->GetName());
		}
		PreselectActors.Empty();
	}
}

void ARTSHUD::GetUnitsInSelectBox(const FVector2D& InFirstPoint, const FVector2D& InSecondPoint, TArray<AActor*>& OutUnits)
{
	OutUnits.Reset();
	FBox2D SelectionRectangle(ForceInit);
	SelectionRectangle += InFirstPoint;
	SelectionRectangle += InSecondPoint;
	for (TActorIterator<AUnitBase> Itr(GetWorld()); Itr; ++Itr)
	{
		AUnitBase* EachActor = *Itr;
		const FVector ProjectedWorldLocation = Project(EachActor->GetActorLocation());
		if (SelectionRectangle.IsInside(FVector2D(ProjectedWorldLocation)))
		{
			OutUnits.Add(EachActor);
		}
	}
}
