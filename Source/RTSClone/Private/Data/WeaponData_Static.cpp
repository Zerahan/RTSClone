// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponData_Static.h"

bool UWeaponData_Static::LoadData(FWeaponData_StaticStruct Data)
{
    if (Data.IsValid()) {
        WeaponData_Static = Data;
    }
    return false;
}


bool UWarheadData_Static::LoadData(FWarheadData_StaticStruct Data)
{
    if (Data.IsValid()) {
        WarheadData_Static = Data;
    }
    return false;
}

FWeaponData_StaticStruct UWeaponData_Static::GetStruct() const { return WeaponData_Static; }
FWarheadData_StaticStruct UWarheadData_Static::GetStruct() const { return WarheadData_Static; }

bool UWeaponData_Static::IsValid() const { return WeaponData_Static.IsValid(); }
bool UWarheadData_Static::IsValid() const { return WarheadData_Static.IsValid(); }

