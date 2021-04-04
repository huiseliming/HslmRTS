// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

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
		const float ScreenX = FirstPoint.X < SecondPoint.X ? FirstPoint.X : SecondPoint.X ;
		const float ScreenY = FirstPoint.Y < SecondPoint.Y ? FirstPoint.Y : SecondPoint.Y ;
		const float Width = FMath::Abs(SecondPoint.X - FirstPoint.X);
		const float Height = FMath::Abs(FirstPoint.Y - SecondPoint.Y);
		//GLog->Log(FString::Printf(TEXT("ScreenX: %f, ScreenY: %f, Width: %f, Height: %f"), ScreenX, ScreenY, Width, Height));
		DrawRect(FLinearColor(0.5,0.5,0.5,0.3), ScreenX, ScreenY, Width, Height);
		DrawLine(ScreenX, ScreenY, ScreenX +Width, ScreenY, FLinearColor::Gray);
		DrawLine(ScreenX +Width, ScreenY,ScreenX + Width, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX + Width, ScreenY + Height, ScreenX, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX, ScreenY + Height, ScreenX, ScreenY, FLinearColor::Gray);
	}
}

void ARTSHUD::SetDrawSelectBox(bool IsDraw)
{
	bIsDrawSelectBox = IsDraw;
}
