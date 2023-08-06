// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitGroup.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RTSCLONE_API FUnitGroup
{
	GENERATED_BODY()
	
	FUnitGroup()
	{};

	UPROPERTY()
	TArray<AActor*> SelectedActors;

	bool AddUnit(AActor* Actor);
	bool RemoveUnit(AActor* Actor);

	void ClearInvalidUnits();

	static const uint8 MAX_SIZE;
};
