// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "UnitData_Static.generated.h"


UENUM(BlueprintType)
enum class EUnitClass : uint8
{
	None		= 0,
	Infantry	= 1,
	Vehicle		= 2,
	Structure	= 3
};

UENUM(BlueprintType)
enum class EAICategory : uint8
{
	Soldier			= 0,
	Civilian		= 1,
	VIP				= 2,
	Ship			= 3,
	Recon			= 4,
	AFV				= 5,
	IFV				= 6,
	LRFS			= 7,
	Support			= 8,
	Transport		= 9,
	AirPower		= 10,
	AirLift			= 11,
	Structure		= 12,
	Power			= 13,
	Defense			= 14,
	Factory			= 15,
	Economy			= 16,
	Construction	= 17
};

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	None		= 0,
	Ground		= 1,
	Amphibious	= 2,
	Hover		= 3,
	Underground	= 4,
	Air			= 5
};

UENUM(BlueprintType)
enum class EBrainType : uint8
{
	None		= 0,
	Infantry	= 1,
	Vehicle		= 2,
	Harvester	= 3,
	Aircraft	= 4,
	Turret		= 5,
	Civilian	= 6
};

USTRUCT(BlueprintType)
struct FUnitData_StaticStruct : public FTableRowBase {
	GENERATED_BODY()

	FUnitData_StaticStruct() {
		ID				= NAME_None;
		DisplayName		= FText::FromString("Unknown Object");
		UnitType		= EUnitClass::None;
		Category		= EAICategory::Soldier;
		MovementType	= EMovementType::None;
		BrainType		= EBrainType::None;
		MeshToUse		= nullptr;
		Health			= 1;
		Speed			= 0;
		SortRank		= "a";
		Factory			= EUnitClass::None;
	}

	// Internal ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ID;

	// Text to display
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	// Display name of the object
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FString SortRank;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EUnitClass UnitType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStaticMesh> MeshToUse;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> IconImage;

	// Category of object used by AI systems
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EAICategory Category;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EMovementType MovementType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EBrainType BrainType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 Cost;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 Health;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FName> PrerequisiteList;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FName> WeaponList;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EUnitClass Factory;

public:
	bool IsValid() const { return ID != NAME_None; }
};

/**
 * 
 */
UCLASS(BlueprintType)
class RTSCLONE_API UUnitData_Static : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* DataTableToLoad;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName RowNameToLoad;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FUnitData_StaticStruct UnitData_Static;

public:
	UFUNCTION(BlueprintCallable)
	bool LoadData(FUnitData_StaticStruct Data);

	UFUNCTION(BlueprintCallable)
	FUnitData_StaticStruct Get() const;

	UFUNCTION(BlueprintCallable)
	bool IsValid() const;
	
};
