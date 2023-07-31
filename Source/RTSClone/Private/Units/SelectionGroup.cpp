// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/SelectionGroup.h"
#include "Interfaces/SelectionInterface.h"
#include "Interfaces/UnitInterface.h"

// Add default functionality here for any ISelectionInterface functions that are not pure virtual.

USelectionGroup::USelectionGroup()
	: Super()
{
}

void USelectionGroup::OnGroupSelected()
{
	ClearInvalidUnitsFromGroup();
	OnUpdateUnitGroup.Broadcast();
}

TArray<AActor*> USelectionGroup::GetSelectedUnits() const
{
	return SelectedUnits;
}

bool USelectionGroup::AddUnit(AActor* Value, bool DoUpdate)
{
	if (!IsValidUnit(Value)) return false;
	if (SelectedUnits.Contains(Value)) return false;
	if (SelectedUnits.Num() > 50) {
		ClearInvalidUnitsFromGroup();
		if (SelectedUnits.Num() > 50) return false;
	}
	SelectedUnits.Add(Value);
	if (DoUpdate) OnUpdateUnitGroup.Broadcast();
	return true;
}

bool USelectionGroup::RemoveUnit(AActor* Value, bool DoUpdate)
{
	if (!IsValid(Value)) return false;
	int32 n = SelectedUnits.Remove(Value);
	if (DoUpdate) OnUpdateUnitGroup.Broadcast();
	return n > 0;
}

void USelectionGroup::ClearInvalidUnitsFromGroup()
{
	for (int32 i = SelectedUnits.Num() - 1; i >= 0; i--) {
		if (!IsValidUnit(SelectedUnits[i])) SelectedUnits.RemoveAt(i);
	}
}

bool USelectionGroup::IsValidUnit(AActor* Value) const
{
	if (!IsValid(Value)) return false;
	if (!Value->GetClass()->ImplementsInterface(USelectionInterface::StaticClass())) return false;
	if (Value->GetClass()->ImplementsInterface(UUnitInterface::StaticClass()) && IUnitInterface::Execute_IsAlive(Value)) return false;
	return true;
}

