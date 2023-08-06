// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "InputManagerComponent.generated.h"

class UInputContext;

UENUM(BlueprintType)
enum class EInputControlMode : uint8
{
	Selection		UMETA(DisplayName = "Selection"),
	UnitControl		UMETA(DisplayName = "UnitControl"),
	BuildingControl	UMETA(DisplayName = "BuildingControl"),
	Construction	UMETA(DisplayName = "Construction"),
	MAX UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EInputControlMode, EInputControlMode::MAX);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVELOPERLIBRARY_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY()
	APlayerController* ControllerRef;

	UPROPERTY()
	UInputComponent* InputComponentRef;

	UPROPERTY()
	TMap<EInputControlMode, UInputContext*> AllContexts;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EInputControlMode, TSubclassOf<UInputContext>> InputContextClasses;

	UPROPERTY()
	UInputContext* CurrentContext;

	UPROPERTY()
	EInputControlMode CurrentControlMode;

	UPROPERTY()
	bool IsInputAllowed;
	
public:
	// Sets default values for this component's properties
	UInputManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent, APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	UInputContext* GetCurrentContext() const;
	
	UFUNCTION(BlueprintCallable)
	EInputControlMode GetControlMode() const;

	UFUNCTION(BlueprintCallable)
	UInputComponent* GetInputComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetControlMode(EInputControlMode Value = EInputControlMode::Selection, UInputData* Data = nullptr);
	virtual void SetControlMode_Implementation(EInputControlMode Value, UInputData* Data);
	
	bool GetIsInputAllowed() const;

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

public:
	UFUNCTION(BlueprintCallable)
	bool IsShiftDown() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsCtrlDown() const;

	UFUNCTION(BlueprintCallable)
	bool IsAltDown() const;
};
