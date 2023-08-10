// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SelectionGroup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateUnitGroup);

/**
 * 
 */
UCLASS(BlueprintType)
class RTSCLONE_API USelectionGroup : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> SelectedUnits;

public:
	static const uint8 MaxGroupSize;

public:
	USelectionGroup();

	// Runs when a saved unit group is reselectedd
	UFUNCTION(BlueprintCallable)
	void OnGroupSelected();

	// Gets all of the units within this unit group
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetSelectedUnits() const;

	// Adds a valid unit to the group if there is capacity for it.
	UFUNCTION(BlueprintCallable)
	bool AddUnit(AActor* Value, bool DoUpdate = true);

	// Remove the first instance of this unit from the group
	UFUNCTION(BlueprintCallable)
	bool RemoveUnit(AActor* Value, bool DoUpdate = true);

	UFUNCTION(BlueprintCallable)
	void ClearInvalidUnitsFromGroup();

	UFUNCTION(BlueprintCallable)
	void Empty(bool DoUpdate = true);

	UFUNCTION(BlueprintCallable)
	bool IsValidUnit(AActor* Value) const;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateUnitGroup OnUpdateUnitGroup;
};
