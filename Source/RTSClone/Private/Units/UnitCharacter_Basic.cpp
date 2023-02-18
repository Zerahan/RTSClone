// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitCharacter_Basic.h"
#include "Data/UnitData_Static.h"

// Sets default values
AUnitCharacter_Basic::AUnitCharacter_Basic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitCharacter_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitCharacter_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitCharacter_Basic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AUnitCharacter_Basic::SetupUnitFromData_Implementation(UUnitData_Static* StaticData) {
	StaticDataRef = StaticData;
	return true;
}

AController* AUnitCharacter_Basic::GetOwningPlayer_Implementation() const { return OwningPlayer; }

UUnitData_Static* AUnitCharacter_Basic::GetUnitStaticData_Implementation() const { return StaticDataRef; }

