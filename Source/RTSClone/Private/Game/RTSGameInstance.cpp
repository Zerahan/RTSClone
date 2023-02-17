// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSGameInstance.h"
#include "Data/UnitData_Static.h"
#include "Data/WeaponData_Static.h"

UUnitData_Static* URTSGameInstance::GetUnitStaticData(FString FromName) const {
	if (UnitList.Contains(FName(FromName))) {
		return UnitList.FindRef(FName(FromName));
	}
	return nullptr;
}

UWeaponData_Static* URTSGameInstance::GetWeaponStaticData(FString FromName) const {
	if (WeaponList.Contains(FName(FromName))) {
		return WeaponList.FindRef(FName(FromName));
	}
	return nullptr;
}

UWarheadData_Static* URTSGameInstance::GetWarheadStaticData(FString FromName) const {
	if (WarheadList.Contains(FName(FromName))) {
		return WarheadList.FindRef(FName(FromName));
	}
	return nullptr;
}
