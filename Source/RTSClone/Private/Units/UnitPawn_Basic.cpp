// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitPawn_Basic.h"
#include "Data/UnitData_Static.h"

// Sets default values
AUnitPawn_Basic::AUnitPawn_Basic()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitPawn_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitPawn_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AUnitPawn_Basic::SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData) {
	StaticDataRef = StaticData;
	return true;
}

AController* AUnitPawn_Basic::GetOwningPlayer_Implementation() const { return OwningPlayer; }

UUnitData_Static* AUnitPawn_Basic::GetUnitStaticData_Implementation() const { return StaticDataRef; }

