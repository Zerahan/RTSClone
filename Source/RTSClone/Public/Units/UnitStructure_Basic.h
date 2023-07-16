// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/UnitInterface.h"
#include "UnitStructure_Basic.generated.h"

//class UUnitData_Static;

UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API AUnitStructure_Basic : public AActor, public IUnitInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	UUnitData_Static* StaticDataRef;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	AController* OwningPlayer;
	
public:	
	// Sets default values for this actor's properties
	AUnitStructure_Basic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData);
	virtual UUnitData_Static* GetUnitStaticData_Implementation() const;
	virtual AController* GetOwningPlayer_Implementation() const;

};
