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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PrimaryAction_Pressed();
	virtual void PrimaryAction_Pressed_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PrimaryAction_Released();
	virtual void PrimaryAction_Released_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SecondaryAction_Pressed();
	virtual void SecondaryAction_Pressed_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SecondaryAction_Released();
	virtual void SecondaryAction_Released_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TertiaryAction_Pressed();
	virtual void TertiaryAction_Pressed_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TertiaryAction_Released();
	virtual void TertiaryAction_Released_Implementation();
};
