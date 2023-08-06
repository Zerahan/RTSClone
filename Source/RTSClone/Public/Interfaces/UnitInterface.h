// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitInterface.generated.h"

class UUnitData_Static;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSCLONE_API IUnitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UUnitData_Static* GetUnitStaticData() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SetupUnitFromDataObject(UUnitData_Static* StaticData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SetupUnit(UUnitData_Static* StaticData, AController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AController* GetOwningPlayer() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SelectUnit();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeselectUnit();
};
