// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSGameInstance.h"
#include "Data/UnitData_Static.h"
#include "Data/WeaponData_Static.h"

// Sets default values
URTSGameInstance::URTSGameInstance()
{
	ColorList.Add("Gold", FLinearColor::Yellow);
	ColorList.Add("Red", FLinearColor::Red);
	ColorList.Add("Blue", FLinearColor::Blue);
	ColorList.Add("Green", FLinearColor::Green);
	ColorList.Add("Orange", FLinearColor(1.f, 0.5f, 0.f));
	ColorList.Add("Cyan", FLinearColor(0.f, 1.f, 1.f));
	ColorList.Add("Purple", FLinearColor(0.5f, 0.f, 1.f));
	ColorList.Add("Pink", FLinearColor(1.f, 0.f, 0.5f));
}

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
