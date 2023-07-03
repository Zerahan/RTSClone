// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ResourceData_Static.generated.h"

USTRUCT(BlueprintType)
struct FResourceData_StaticStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	FResourceData_StaticStruct()
		: ID(NAME_None)
		, DisplayName(FText::FromString("Unknown Object"))
		, MeshToUse(nullptr)
		, Transform(FTransform())
		, ValuePerUnit(0.f)
	{}

	// Internal ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName ID;

	// Text to display
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStaticMesh> MeshToUse;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FTransform Transform;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float ValuePerUnit;

public:
	bool IsValid() const { return ID != NAME_None; }
};

/**
 * 
 */
UCLASS(BlueprintType)
class RTSCLONE_API UResourceData_Static : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* DataTableToLoad;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName RowNameToLoad;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FResourceData_StaticStruct ResourceData_Static;

public:
	UFUNCTION(BlueprintCallable)
	bool LoadData(FResourceData_StaticStruct Data);

	UFUNCTION(BlueprintCallable)
	FResourceData_StaticStruct Get() const;

	UFUNCTION(BlueprintCallable)
	bool IsValid() const;
	
};
