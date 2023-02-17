// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RTSGameInstance.generated.h"

class UUnitData_Static;
class UWeaponData_Static;
class UWarheadData_Static;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API URTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FName, UUnitData_Static*> UnitList;

	UPROPERTY()
	TMap<FName, UWeaponData_Static*> WeaponList;

	UPROPERTY()
	TMap<FName, UWarheadData_Static*> WarheadList;

public:
	UFUNCTION(BlueprintCallable)
	UUnitData_Static* GetUnitStaticData(FString FromName) const;
	
	UFUNCTION(BlueprintCallable)
	UWeaponData_Static* GetWeaponStaticData(FString FromName) const;

	UFUNCTION(BlueprintCallable)
	UWarheadData_Static* GetWarheadStaticData(FString FromName) const;
	
};
