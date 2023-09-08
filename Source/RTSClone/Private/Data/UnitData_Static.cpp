// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UnitData_Static.h"

bool UUnitData_Static::LoadData(FUnitData_StaticStruct Data)
{
    if (Data.IsValid()) {
        UnitData_Static = Data;
    }
    return false;
}

FUnitData_StaticStruct UUnitData_Static::GetStruct() const { return UnitData_Static; }

bool UUnitData_Static::IsValid() const { return UnitData_Static.IsValid(); }

UUnitData_Static* UUnitData_Static::BuildDataFromTable(UObject* OwnerRef, UDataTable* Table, FName Row)
{
	if (!OwnerRef->IsValidLowLevel()) { UE_LOG(LogTemp, Warning, TEXT("UnitData_Static::BuildDataFromTable | Attemted to build using invalid OwnerRef object.")); return nullptr; }
	if (!Table->IsValidLowLevel()) { UE_LOG(LogTemp, Warning, TEXT("UnitData_Static::BuildDataFromTable | Attemted to build using invalid Table object. Owner: %s"), *OwnerRef->GetName()); return nullptr; }
	UUnitData_Static* UnitDataRef = NewObject<UUnitData_Static>(OwnerRef);
	if (UnitDataRef->LoadData(*Table->FindRow<FUnitData_StaticStruct>(Row, ""))) return UnitDataRef;
	UE_LOG(LogTemp, Warning, TEXT("UnitData_Static::BuildDataFromTable | Attemted to build using invalid Row object. Owner: %s, Table: %s, Row: %s"), *OwnerRef->GetName(), *Table->GetName(), *Row.ToString());
	return nullptr;
}

