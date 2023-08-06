// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/UnitInterface.h"
#include "Interfaces/SelectionInterface.h"
#include "UnitStructure_Basic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPrimarySet, bool, IsPrimary);

//class UUnitData_Static;

UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API AUnitStructure_Basic : public AActor, public IUnitInterface, public ISelectionInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	UUnitData_Static* StaticDataRef;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	AController* OwningPlayer;

	UPROPERTY()
	bool IsPrimaryFactory;
	
public:
	// Sets default values for this actor's properties
	AUnitStructure_Basic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

	virtual bool SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData);
	virtual bool SetupUnit_Implementation(UUnitData_Static* StaticData, AController* Controller);
	virtual UUnitData_Static* GetUnitStaticData_Implementation() const;
	virtual AController* GetOwningPlayer_Implementation() const;

	UFUNCTION(BlueprintCallable)
	void SetOwningPlayer(AController* Controller);

	UFUNCTION(BlueprintCallable)
	uint8 GetTeamID() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsPrimaryFactory() const;

	UFUNCTION(BlueprintCallable)
	void SetIsPrimaryFactory(bool Value);
	
	UPROPERTY(BlueprintAssignable)
	FOnPrimarySet OnPrimarySet;
};
