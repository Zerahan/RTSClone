// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputManager/InputContext.h"
#include "Selection_IC.generated.h"

class USelectionGroup;

/**
 * 
 */
UCLASS()
class RTSCLONE_API USelection_IC : public UInputContext
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<USelectionGroup*> SavedSelectionGroups;

	UPROPERTY()
	USelectionGroup* ActiveSelectionGroup;

public:
	virtual bool PrimaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown) override;
};
