// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "WeaponData_Static.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData_StaticStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	FWeaponData_StaticStruct()
		: ID(NAME_None)
		, Damage(0)
		, ROF(15)
		, Range(1)
		, Warhead(NAME_None)
	{};

	// Internal ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ID;

	// "the amount of damage (unattenuated) dealt with every bullet"
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 Damage;

	// "delay between shots [15 = 1 second at middle speed setting]"
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 ROF;

	// "maximum cell range"
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 Range;

	// "warhead to attach to projectile"
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName Warhead;

public:
	bool IsValid() const { return ID != NAME_None; }
};

USTRUCT(BlueprintType)
struct FWarheadData_StaticStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	FWarheadData_StaticStruct()
		: ID(NAME_None)
	{
		Verses.SetNumZeroed(5);
	}

	// Internal ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName ID;
	
	// "damage value verses various armor types (as percentage of full damage)..."
	// "          -vs - none, wood(buildings), light armor, heavy armor, concrete"
	UPROPERTY(EditFixedSize, BlueprintReadOnly, EditDefaultsOnly)
	TArray<float> Verses;

public:
	bool IsValid() const { return ID != NAME_None; }
};

/**
 * 
 */
UCLASS(BlueprintType)
class RTSCLONE_API UWeaponData_Static : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FWeaponData_StaticStruct WeaponData_Static;

public:
	UFUNCTION(BlueprintCallable)
	bool LoadData(FWeaponData_StaticStruct Data);

	UFUNCTION(BlueprintCallable)
	FWeaponData_StaticStruct GetStruct() const;

	UFUNCTION(BlueprintCallable)
	bool IsValid() const;
};

/**
 *
 */
UCLASS(BlueprintType)
class RTSCLONE_API UWarheadData_Static : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FWarheadData_StaticStruct WarheadData_Static;

public:
	UFUNCTION(BlueprintCallable)
	bool LoadData(FWarheadData_StaticStruct Data);

	UFUNCTION(BlueprintCallable)
	FWarheadData_StaticStruct GetStruct() const;

	UFUNCTION(BlueprintCallable)
	bool IsValid() const;
};
