// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/TeamTypes.h"
#include "RTSHandlerComponent.generated.h"

UENUM(BlueprintType)
enum class EControlMode : uint8
{
	Default,
	Placement,
	Command,
	Repair,
	Power
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateControlMode, EControlMode, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSCLONE_API URTSHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	EControlMode ControlMode;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_SetTeam)
	ERTSTeam MyTeam;

public:	
	// Sets default values for this component's properties
	URTSHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void TestFunction();

	UFUNCTION(BlueprintCallable)
	void OnPrimaryPressed();
	
	UFUNCTION(BlueprintCallable)
	void OnPrimaryReleased();

	UFUNCTION(BlueprintCallable)
	void OnSecondaryPressed();

	UFUNCTION(BlueprintCallable)
	void OnSecondaryReleased();

	UFUNCTION(BlueprintCallable)
	EControlMode GetControlMode() const;

	UFUNCTION(BlueprintCallable)
	void SetControlMode(EControlMode Value = EControlMode::Default);

	UFUNCTION(BlueprintCallable)
	ERTSTeam GetTeam() const;

	UFUNCTION(BlueprintCallable, SERVER, Reliable)
	void SERVER_SetTeam(ERTSTeam Value);
	void SERVER_SetTeam_Implementation(ERTSTeam Value);

	UFUNCTION()
	virtual void OnRep_SetTeam(ERTSTeam Value);

	UPROPERTY(BlueprintAssignable)
	FOnUpdateControlMode OnUpdateControlMode;
};
