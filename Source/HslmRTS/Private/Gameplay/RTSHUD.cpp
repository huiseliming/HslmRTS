// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/RTSHUD.h"

#include "EngineUtils.h"
#include "HslmRTS.h"
#include "RTSActor.h"
#include "UnitBase.h"

ARTSHUD::ARTSHUD()
{
	bIsSelecting = false;
	SelectedActorsCounter = 0;
	PreselectedActorsCounter = 0;
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
	if (bIsSelecting)
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
		if((FirstPoint - SecondPoint).SizeSquared() < 100.f){
			UpdatePreselectedActorUnderCursor();
		}else{
			UpdatePreselectedActorsInBox();
		}
	}else{
		UpdatePreselectedActorUnderCursor();
	}
}

void ARTSHUD::UpdatePreselectedActorUnderCursor()
{
	FHitResult HitResult;
    if(GetOwningPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
    {
    	AActor* HitActor = HitResult.Actor.Get();
    	if(HitActor && PreselectedActors.Num() == 1 && PreselectedActors[0] == HitActor) 
    	{
    		return;
    	}
    	for (int32 i = 0; i < PreselectedActors.Num(); i++)
    	{
    		if(PreselectedActors[i] == HitActor)
    		{
    			if (i != 0)
    			{
    				PreselectedActors.Swap(0,i);
    			}
    		}
    		else
    		{
    			OnActorUnpreselected(PreselectedActors[i]);
    		}
    	}
    	PreselectedActors.SetNum(1);
    	if(PreselectedActors[0] != HitActor)
    	{
    		OnActorPreselected(HitActor);
    		PreselectedActors[0] = HitActor;
    	}
    }
}

void ARTSHUD::UpdatePreselectedActorsInBox()
{
	TArray<AActor*> OldPreselectActors;
	Swap(PreselectedActors,OldPreselectActors);
	//GetUnitsInSelectBox(FirstPoint, SecondPoint, PreselectActors);
	GetActorsInSelectionRectangle(AUnitBase::StaticClass() ,FirstPoint, SecondPoint,PreselectedActors,false ,false);
	PreselectedActors.Sort();//[](AActor** A, AActor** B) mutable { return A < B; });
	Algo::Sort(PreselectedActors,[](const AActor* A, const AActor* B) { return A < B; });
	if(PreselectedActors.Num() == 0)
	{
		for (AActor* OldPreselectActor : OldPreselectActors)
		{
			OnActorUnpreselected(OldPreselectActor);
		}
	}else{
		int32 PreselectActorsIndex = 0;
		for (int32 i = 0; i < OldPreselectActors.Num(); i++){
			while (PreselectActorsIndex < PreselectedActors.Num() && OldPreselectActors[i] > PreselectedActors[PreselectActorsIndex]){
				OnActorPreselected(PreselectedActors[PreselectActorsIndex]);
				PreselectActorsIndex++;
			}
			if(PreselectActorsIndex >= PreselectedActors.Num())
			{
				OnActorUnpreselected(OldPreselectActors[i]);
				continue;
			}else if(OldPreselectActors[i] < PreselectedActors[PreselectActorsIndex]){
				OnActorUnpreselected(OldPreselectActors[i]);
			}else if(OldPreselectActors[i] == PreselectedActors[PreselectActorsIndex]){
				PreselectActorsIndex++;
			}
		}
		while (PreselectActorsIndex < PreselectedActors.Num()){
			OnActorPreselected(PreselectedActors[PreselectActorsIndex]);
			PreselectActorsIndex++;
		}
	}
}

void ARTSHUD::DoSelectStart()
{
	bIsSelecting = true;
	GetOwningPlayerController()->GetMousePosition(FirstPoint.X, FirstPoint.Y);
}

void ARTSHUD::DoSelectFinish()
{
	if ((FirstPoint - SecondPoint).SizeSquared() < 100.f)
	{
		DoSingleSelect();
	}else
	{
		DoBoxSelect();
	}
	bIsSelecting = false;
}

void ARTSHUD::DoSingleSelect()
{
	if (PreselectedActors.IsValidIndex(0))
	{
		ARTSActor* RTSActor = Cast<ARTSActor>(PreselectedActors[0]);
		if(RTSActor)
		{
			SelectSingleActor(RTSActor);
			return;
		}
		AUnitBase* Unit = Cast<AUnitBase>(PreselectedActors[0]);
		if(Unit)
		{
			SelectSingleActor(Unit);
			return;
		}
	}
}

void ARTSHUD::DoBoxSelect()
{
	if(PreselectedActors.Num() > 0)
	{
		SelectActors(PreselectedActors);
	}
}

void ARTSHUD::ClearPreselectActors()
{
	for (AActor* PreselectActor : PreselectedActors)
	{
		OnActorUnpreselected(PreselectActor);
	}
	PreselectedActors.Empty();
}

void ARTSHUD::ClearSelectedActors()
{
	for (AActor* SelectedActor : SelectedActors)
	{
		OnActorUnselected(SelectedActor);
	}
	SelectedActors.Empty();
}

void ARTSHUD::SelectSingleActor(AActor* Actor)
{
	ClearSelectedActors();
	SelectedActors.Add(Actor);
	FocusedActor = Actor;
	OnActorSelected(Actor);
}

void ARTSHUD::SelectActors(TArray<AActor*>& Actors)
{
	check(Actors.Num() > 0)
	ClearSelectedActors();
	SelectedActors = Actors;
	FocusedActor = Actors[0];
	for (auto& Actor : Actors)
	{
		OnActorSelected(Actor);
	}
}

void ARTSHUD::OnActorSelected(AActor* Actor)
{
	SelectedActorsCounter++;
	UE_LOG(LogHslmRTS, Log, TEXT("SelectedActorsCounter    = %d, Select      %s"), SelectedActorsCounter, *Actor->GetName());
}

void ARTSHUD::OnActorUnselected(AActor* Actor)
{
	SelectedActorsCounter--;
	UE_LOG(LogHslmRTS, Log, TEXT("SelectedActorsCounter    = %d, Unselect    %s"), SelectedActorsCounter, *Actor->GetName());
}

void ARTSHUD::OnActorPreselected(AActor* Actor)
{
	PreselectedActorsCounter++;
	UE_LOG(LogHslmRTS, Log, TEXT("PreselectedActorsCounter = %d, Preselect   %s"), PreselectedActorsCounter, *Actor->GetName());
}

void ARTSHUD::OnActorUnpreselected(AActor* Actor)
{
	PreselectedActorsCounter--;
	UE_LOG(LogHslmRTS, Log, TEXT("PreselectedActorsCounter = %d, Unpreselect %s"), PreselectedActorsCounter, *Actor->GetName());
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
