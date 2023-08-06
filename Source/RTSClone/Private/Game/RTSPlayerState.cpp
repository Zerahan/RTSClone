// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSPlayerState.h"
#include "Engine/DataTable.h"
#include "Game/RTSGameMode_Multiplayer.h"
#include "Data/UnitData_Static.h"
#include "Units/SelectionGroup.h"

void ARTSPlayerState::SetupNewState_Implementation(UDataTable* AllPossibleConstructedUnits)
{
	AllUnits = AllPossibleConstructedUnits;
	if(!AllUnits) return;
	for(FName RowName : AllUnits->GetRowNames()){
		FUnitData_StaticStruct* StaticData = AllUnits->FindRow<FUnitData_StaticStruct>(RowName, FString());
		switch (StaticData->UnitType) {
			case EUnitClass::Structure:
				AvailableStructures.Add(RowName, false);
				break;
			case EUnitClass::Infantry: AvailableInfantry.Add(RowName, false); break;
			case EUnitClass::Vehicle: AvailableVehicles.Add(RowName, false); break;
			default: break;
		}
	}
	UpdateAvailableConstructions();
}

void ARTSPlayerState::UpdateAvailableConstructions_Implementation(FName InstigatingName, bool IsConstructed)
{
	bool UpdateAll = InstigatingName == NAME_None;
	if(!UpdateAll && IsTypeAvailable(InstigatingName)){
		if(!IsConstructed) return;	// No update is necissary if there are still units of that type on the map.
		if(OwnedUnitTypes[InstigatingName] > 1) return;  // No update is necissary if there were already units of that type on the map.
	}
	
	//FUnitData_StaticStruct Data;
	bool ChangeFound = false;
	FString Context;

	TArray<FName> Keys;
	//Update available structures
	AvailableStructures.GetKeys(Keys);
	for (FName RowName : Keys) {
		FUnitData_StaticStruct* Data = AllUnits->FindRow<FUnitData_StaticStruct>(RowName, Context);
		//if(!Data->IsValid()) continue;
		if (!UpdateAll && !Data->PrerequisiteList.Contains(InstigatingName)) continue; // Skip if the instigator is not a prerequisite.
		bool CanNotBuild = false; // True if there are any types on the prerequisit list that have no units.
		for (FName Name : Data->PrerequisiteList) {
			if (!IsTypeAvailable(Name)) CanNotBuild = true;
		}
		if(!ChangeFound && AvailableStructures[RowName] == CanNotBuild) ChangeFound = true;
		AvailableStructures.Add(RowName, !CanNotBuild);
	}
	
	//Update available infantry
	AvailableInfantry.GetKeys(Keys);
	for (FName RowName : Keys) {
		FUnitData_StaticStruct* Data = AllUnits->FindRow<FUnitData_StaticStruct>(RowName, Context);
		if (!UpdateAll && !Data->PrerequisiteList.Contains(InstigatingName)) continue; // Skip if the instigator is not a prerequisite.
		bool CanNotBuild = false;
		for (FName Name : Data->PrerequisiteList) {
			if (!IsTypeAvailable(Name)) CanNotBuild = true;
		}
		if (!ChangeFound && AvailableInfantry[RowName] == CanNotBuild) ChangeFound = true;
		AvailableInfantry.Add(RowName, !CanNotBuild);
	}

	//Update available vehicles
	AvailableVehicles.GetKeys(Keys);
	for (FName RowName : Keys) {
		FUnitData_StaticStruct* Data = AllUnits->FindRow<FUnitData_StaticStruct>(RowName, Context);
		if (!UpdateAll && !Data->PrerequisiteList.Contains(InstigatingName)) continue; // Skip if the instigator is not a prerequisite.
		bool CanNotBuild = false;
		for (FName Name : Data->PrerequisiteList) {
			if (!IsTypeAvailable(Name)) CanNotBuild = true;
		}
		if (!ChangeFound && AvailableVehicles[RowName] == CanNotBuild) ChangeFound = true;
		AvailableVehicles.Add(RowName, !CanNotBuild);
	}
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Green,FString::Printf(TEXT("Constructions updated!")));
	if(ChangeFound)	OnUpdateAvailableConstructions.Broadcast();
}

UDataTable* ARTSPlayerState::GetDataTable_AllUnits() const { return AllUnits; }

TArray<FName> ARTSPlayerState::GetAvailableStructures(bool GetAll) const
{
	TArray<FName> UnitList;
	if(GetAll){
		AvailableStructures.GetKeys(UnitList);
	}
	else {
		for (TPair<FName,bool> pair : AvailableStructures) {
			if(pair.Value) UnitList.Add(pair.Key);
		}
	}
	return UnitList;
}

TArray<FName> ARTSPlayerState::GetAvailableInfantry(bool GetAll) const
{
	TArray<FName> UnitList;
	if (GetAll) {
		AvailableInfantry.GetKeys(UnitList);
	}
	else {
		for (TPair<FName, bool> pair : AvailableInfantry) {
			if (pair.Value) UnitList.Add(pair.Key);
		}
	}
	return UnitList;
}

TArray<FName> ARTSPlayerState::GetAvailableVehicles(bool GetAll) const
{
	TArray<FName> UnitList;
	if (GetAll) {
		AvailableVehicles.GetKeys(UnitList);
	}
	else {
		for (TPair<FName, bool> pair : AvailableVehicles) {
			if (pair.Value) UnitList.Add(pair.Key);
		}
	}
	return UnitList;
}

bool ARTSPlayerState::IsTypeAvailable(FName Type) const
{
	if(!OwnedUnitTypes.Contains(Type)) return false;
	return OwnedUnitTypes[Type] != 0;
}

void ARTSPlayerState::RegisterPerminantAvailableType(FName Type, bool ManualUpdate)
{
	OwnedUnitTypes.Add(Type, (OwnedUnitTypes.Contains(Type) ? OwnedUnitTypes[Type] : 0) + 1);
	if(!ManualUpdate) UpdateAvailableConstructions(Type, true);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Added perminant type: %s"), *Type.ToString()));
}

void ARTSPlayerState::RegisterUnit(AActor* UnitRef, FName Type, bool ManualUpdate)
{
	OwnedUnits.Add(UnitRef);
	OwnedUnitTypes.Add(Type, (OwnedUnitTypes.Contains(Type) ? OwnedUnitTypes[Type] : 0) + 1);
	if (!ManualUpdate) UpdateAvailableConstructions(Type, true);
}

void ARTSPlayerState::UnregisterUnit(AActor* UnitRef, FName Type, bool ManualUpdate)
{
	OwnedUnits.RemoveSingle(UnitRef);
	OwnedUnitTypes.Add(Type, FMath::Max((OwnedUnitTypes.Contains(Type) ? OwnedUnitTypes[Type] : 0) - 1, 0));
	if (!ManualUpdate) UpdateAvailableConstructions(Type, false);
}
