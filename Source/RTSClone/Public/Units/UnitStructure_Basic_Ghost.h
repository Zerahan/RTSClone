// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/UnitInterface.h"
#include "UnitStructure_Basic_Ghost.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API AUnitStructure_Basic_Ghost : public AActor, public IUnitInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	UUnitData_Static* StaticDataRef;
	
public:	
	// Sets default values for this actor's properties
	AUnitStructure_Basic_Ghost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool SetupUnitFromData_Implementation(UUnitData_Static* StaticData);
	virtual UUnitData_Static* GetUnitStaticData_Implementation() const;
};
