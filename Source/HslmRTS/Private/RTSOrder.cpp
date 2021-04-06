#include "RTSOrder.h"


FMoveToLocationOrder::FMoveToLocationOrder(FVector Goal)
	:GoalLocation(Goal)
{
}

bool FMoveToLocationOrder::operator()(AUnitBase* Unit)
{
	Unit->MoveToLocation(GoalLocation);
	return true;
}

FRTSOrderQueue::FRTSOrderQueue()
{
	LastIndex = 0;
}

void FRTSOrderQueue::PushOrder(TSharedPtr<IRTSOrder> RTSOrder)
{
	RTSOrders.Add(RTSOrder);
}

TSharedPtr<IRTSOrder> FRTSOrderQueue::PopOrder()
{
	if (RTSOrders.IsValidIndex(LastIndex))
	{
		TSharedPtr<IRTSOrder> RTSOrder = RTSOrders[LastIndex];
		LastIndex++;
		return RTSOrder;
	}
	ClearOrder();
	return TSharedPtr<IRTSOrder>();
}

void FRTSOrderQueue::ClearOrder()
{
	RTSOrders.Empty();
	LastIndex = 0;
}
