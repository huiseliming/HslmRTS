// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UnitBase.h"

struct HSLMRTS_API IRTSOrder
{
	IRTSOrder() = default;
	virtual ~IRTSOrder() = default;
	virtual bool operator()(AUnitBase* Unit) = 0;
};

struct HSLMRTS_API FMoveToLocationOrder : public IRTSOrder
{
	FMoveToLocationOrder(FVector Goal);
	virtual bool operator()(AUnitBase* Unit) override;
	FVector GoalLocation;
};

struct HSLMRTS_API FRTSOrderQueue
{
	FRTSOrderQueue();
	void PushOrder(TSharedPtr<IRTSOrder>);
	TSharedPtr<IRTSOrder> PopOrder();
	void ClearOrder();
	int32 LastIndex;
	TArray<TSharedPtr<IRTSOrder>> RTSOrders;
};