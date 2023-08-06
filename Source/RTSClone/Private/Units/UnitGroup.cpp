// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitGroup.h"
#include "Interfaces/UnitInterface.h"

const uint8 FUnitGroup::MAX_SIZE(50);

bool FUnitGroup::AddUnit(AActor* Actor)
{
	if (SelectedActors.Num() == MAX_SIZE) ClearInvalidUnits();
	if (SelectedActors.Num() == MAX_SIZE) return false;
	if (!Actor->GetClass()->ImplementsInterface(UUnitInterface::StaticClass())) return false;
	if(!IUnitInterface::Execute_SelectUnit(Actor)) return false;
	return SelectedActors.AddUnique(Actor) != INDEX_NONE;
}

bool FUnitGroup::RemoveUnit(AActor* Actor)
{
	ClearInvalidUnits();
	if (IsValid(Actor)) { if (Actor->GetClass()->ImplementsInterface(UUnitInterface::StaticClass())) IUnitInterface::Execute_DeselectUnit(Actor); }
	return SelectedActors.Remove(Actor) != 0;
}

void FUnitGroup::ClearInvalidUnits()
{
	for (int32 i=SelectedActors.Num()-1; i >= 0; i--) {
		if(!IsValid(SelectedActors[i])) SelectedActors.RemoveAt(i);
	}
}
