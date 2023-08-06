// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UnitData_Static.h"

UUnitData_Static::UUnitData_Static()
	: Super()
{
}

UUnitData_Static::UUnitData_Static(FUnitData_StaticStruct Data)
	: Super()
{
	LoadData(Data);
}

bool UUnitData_Static::LoadData(FUnitData_StaticStruct Data)
{
    if (Data.IsValid()) {
        UnitData_Static = Data;
		return true;
    }
    return false;
}

FUnitData_StaticStruct UUnitData_Static::GetStruct() const { return UnitData_Static; }

bool UUnitData_Static::IsValid() const { return UnitData_Static.IsValid(); }

