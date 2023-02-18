// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/UnitInterface.h"
#include "UnitCharacter_Basic.generated.h"

//class UUnitData_Static;

UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API AUnitCharacter_Basic : public ACharacter, public IUnitInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	UUnitData_Static* StaticDataRef;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	AController* OwningPlayer;

public:
	// Sets default values for this character's properties
	AUnitCharacter_Basic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UUnitData_Static* GetUnitStaticData_Implementation() const;
	virtual bool SetupUnitFromData_Implementation(UUnitData_Static* StaticData);
	virtual AController* GetOwningPlayer_Implementation() const;

};
