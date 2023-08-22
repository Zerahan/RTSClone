// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputContext.generated.h"

class UInputData;
class UInputManagerComponent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DEVELOPERLIBRARY_API UInputContext : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	APawn* PawnRef;

	UPROPERTY()
	APlayerController* ControllerRef;

	UPROPERTY()
	UInputManagerComponent* InputManagerRef;

	UPROPERTY()
	float PrimaryStartHold;

	UPROPERTY()
	float SecondaryStartHold;

	UPROPERTY()
	float TertiaryStartHold;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TickComponent(float DeltaTime);
	virtual void TickComponent_Implementation(float DeltaTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* SpawnActorFromClass(TSubclassOf<AActor> ActorClass, FTransform Transform);
	virtual AActor* SpawnActorFromClass_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartContext(UInputData* Data = nullptr);
	virtual void StartContext_Implementation(UInputData* Data = nullptr);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndContext();
	virtual void EndContext_Implementation();
	
	UFUNCTION(BlueprintCallable)
	void Setup(UInputManagerComponent* Manager, APawn* Pawn = nullptr, APlayerController* Controller = nullptr);

	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn() const;

	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerController() const;

	UFUNCTION(BlueprintCallable)
	UInputManagerComponent* GetInputManager() const;

	UFUNCTION(BlueprintCallable)
	bool IsPrimaryActionDown() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsPrimaryActionHeld() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsSecondaryActionDown() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsSecondaryActionHeld() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsTertiaryActionDown() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsTertiaryActionHeld() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool PrimaryAction_Pressed(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool PrimaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool PrimaryAction_Released(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool PrimaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SecondaryAction_Pressed(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool SecondaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SecondaryAction_Released(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool SecondaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TertiaryAction_Pressed(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool TertiaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TertiaryAction_Released(bool IsShiftDown = false, bool IsCtrlDown = false, bool IsAltDown = false);
	virtual bool TertiaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown);

#if WITH_EDITORONLY_DATA
	void PrintInput(FString Msg, bool IsShiftDown, bool IsCtrlDown, bool IsAltDown) const;
#endif
};
