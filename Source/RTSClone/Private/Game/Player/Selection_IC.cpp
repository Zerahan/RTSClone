// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Player/Selection_IC.h"
#include "Interfaces/SelectionInterface.h"
#include "Units/SelectionGroup.h"

bool USelection_IC::PrimaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	return Super::PrimaryAction_Released_Implementation(IsShiftDown, IsCtrlDown, IsAltDown);
	FHitResult HitResult;
	GetPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
	AActor* ClickedActor = HitResult.GetActor();
	if(!IsValid(ClickedActor)) return false;
	if(!ClickedActor->StaticClass()->ImplementsInterface(USelectionInterface::StaticClass())) return false;
	if (!IsValid(ActiveSelectionGroup)) {
		ActiveSelectionGroup = NewObject<USelectionGroup>(this);
	}
	if (!IsShiftDown) {
		ActiveSelectionGroup->Empty(false);
	}
	ActiveSelectionGroup->AddUnit(ClickedActor);
}
